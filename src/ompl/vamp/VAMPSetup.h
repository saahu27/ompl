/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2015, Rice University
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Rice University nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

/* Author: Sahruday Patti */

#ifndef OMPL_VAMP_VAMP_SETUP_
#define OMPL_VAMP_VAMP_SETUP_

#include <ompl/vamp/VampStateSpace.h>
#include <ompl/vamp/VampStateValidityChecker.h>
#include <ompl/vamp/VampMotionValidator.h>
#include <ompl/vamp/Utils.h>

#include <ompl/base/SpaceInformation.h>
#include <ompl/base/ProblemDefinition.h>
#include <ompl/base/Planner.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/PathGeometric.h>
#include <ompl/tools/benchmark/Benchmark.h>

#include <vamp/collision/environment.hh>
#include <vamp/collision/factory.hh>

#include <memory>
#include <vector>
#include <array>
#include <string>
#include <map>
#include <functional>
#include <chrono>
#include <sstream>
#include <iomanip>

namespace ompl::vamp
{

    /** \brief Convenience setup for VAMP-accelerated motion planning with any OMPL planner.
     *
     * VAMPSetup wraps the existing VampStateSpace, VampStateValidityChecker, and
     * VampMotionValidator into a single setup object that follows OMPL's SimpleSetup
     * pattern. It manages the collision environment and provides convenience methods
     * for configuring problems and running benchmarks.
     *
     * @par Usage
     * @code
     * vamp::collision::Environment<float> env;
     * env.spheres.emplace_back(vamp::collision::factory::sphere::array({0.5f, 0.0f, 0.5f}, 0.1f));
     * env.sort();
     *
     * ompl::vamp::VAMPSetup<vamp::robots::Panda> setup(env);
     * setup.setStartGoal({0, -0.785, 0, -2.356, 0, 1.571, 0.785},
     *                    {2.35, 1.0, 0, -0.8, 0, 2.5, 0.785});
     * setup.setPlanner(std::make_shared<ompl::geometric::RRTConnect>(setup.getSpaceInformation()));
     * setup.solve(5.0);
     * @endcode
     *
     * @tparam Robot VAMP robot type (e.g., vamp::robots::Panda, vamp::robots::UR5)
     * @tparam rake SIMD width for vectorized collision checking (defaults to hardware width)
     */
    template <typename Robot, std::size_t rake = ::vamp::FloatVectorWidth>
    class VAMPSetup
    {
    public:
        using Environment = ::vamp::collision::Environment<::vamp::FloatVector<rake>>;

        explicit VAMPSetup(const ::vamp::collision::Environment<float> &environment)
          : env_(environment), ss_(std::make_shared<VampStateSpace<Robot>>())
        {
            auto si = ss_.getSpaceInformation();
            si->setStateValidityChecker(std::make_shared<VampStateValidityChecker<Robot, rake>>(si, env_));
            si->setMotionValidator(std::make_shared<VampMotionValidator<Robot, rake>>(si, env_));
        }

        void setStartGoal(const std::vector<double> &start, const std::vector<double> &goal)
        {
            ompl::base::ScopedState<> s(ss_.getStateSpace());
            ompl::base::ScopedState<> g(ss_.getStateSpace());
            for (std::size_t i = 0; i < Robot::dimension; ++i)
            {
                s[i] = start[i];
                g[i] = goal[i];
            }
            ss_.setStartAndGoalStates(s, g);
        }

        void setPlanner(const ompl::base::PlannerPtr &planner)
        {
            ss_.setPlanner(planner);
        }

        ompl::base::PlannerStatus solve(double timeout)
        {
            return ss_.solve(timeout);
        }

        ompl::geometric::SimpleSetup &getSimpleSetup()
        {
            return ss_;
        }

        ompl::base::SpaceInformationPtr getSpaceInformation() const
        {
            return ss_.getSpaceInformation();
        }

        ompl::base::StateSpacePtr getStateSpace() const
        {
            return ss_.getStateSpace();
        }

        ompl::geometric::PathGeometric &getSolutionPath()
        {
            return ss_.getSolutionPath();
        }

        const Environment &getEnvironment() const
        {
            return env_;
        }

        void clear()
        {
            ss_.clear();
        }

        /** \brief Run a benchmark comparing multiple planners on the current problem.
         *
         * @param planners Map of planner name to factory function
         * @param runs Number of runs per planner
         * @param timeout Time limit per run in seconds
         * @param experimentName Name for the benchmark experiment
         * @return Path to the generated log file
         */
        std::string benchmark(
            const std::map<std::string,
                           std::function<ompl::base::PlannerPtr(const ompl::base::SpaceInformationPtr &)>> &planners,
            unsigned int runs = 50, double timeout = 5.0,
            const std::string &experimentName = "VAMP Benchmark")
        {
            ompl::tools::Benchmark b(ss_, experimentName);
            b.addExperimentParameter("robot", "STRING", std::string(Robot::name));
            b.addExperimentParameter("dimension", "INTEGER", std::to_string(Robot::dimension));
            b.addExperimentParameter("simd_width", "INTEGER", std::to_string(rake));

            auto si = ss_.getSpaceInformation();
            for (const auto &[name, factory] : planners)
                b.addPlanner(factory(si), name);

            ompl::tools::Benchmark::Request request(timeout, 4096.0, runs);
            b.benchmark(request);

            std::string filename = generateLogFilename(experimentName);
            b.saveResultsToFile(filename.c_str());
            return filename;
        }

    private:
        Environment env_;
        ompl::geometric::SimpleSetup ss_;

        std::string generateLogFilename(const std::string & /*name*/) const
        {
            auto now = std::chrono::system_clock::now();
            auto t = std::chrono::system_clock::to_time_t(now);
            std::ostringstream oss;
            oss << "vamp_" << Robot::name << "_" << std::put_time(std::localtime(&t), "%Y%m%d_%H%M%S") << ".log";
            return oss.str();
        }
    };

}  // namespace ompl::vamp

#endif

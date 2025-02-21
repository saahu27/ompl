#ifndef MOTION_PLANNER_HPP
#define MOTION_PLANNER_HPP

#include "Robot_Model.hpp"
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <Eigen/Dense>
#include <memory>

namespace og = ompl::geometric;
namespace ob = ompl::base;

class MotionPlanner {
public:
    /// Constructor that takes a pointer to a RobotModel.
    MotionPlanner(RobotModel* robot_model);

    /// Plan a motion from start to goal in the robot's configuration space.
    /// @param start A vector representing the start configuration.
    /// @param goal A vector representing the goal configuration.
    /// @param planningTime Maximum planning time in seconds.
    /// @return True if a solution was found.
    bool plan(const Eigen::VectorXd &start, const Eigen::VectorXd &goal, double planningTime = 5.0);

    /// Retrieve the solution path if one was found.
    og::PathGeometric getSolutionPath() const;

private:
    RobotModel* robot_model_;
    std::shared_ptr<og::SimpleSetup> simple_setup_;
};

#endif // MOTION_PLANNER_HPP

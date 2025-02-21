#include "Motion_Planner.hpp"
#include <iostream>
#include <ompl/geometric/planners/rrt/RRTConnect.h>

namespace ob = ompl::base;
namespace og = ompl::geometric;

MotionPlanner::MotionPlanner(RobotModel* robot_model)
    : robot_model_(robot_model)
{
    int dof = robot_model_->getDOF();
    // Create an n-dimensional RealVectorStateSpace.
    auto space = std::make_shared<ob::RealVectorStateSpace>(dof);

    // Set the bounds for each joint.
    ob::RealVectorBounds bounds(dof);
    const auto &model = robot_model_->getModel();
    if(model.lowerPositionLimit.size() == static_cast<size_t>(dof) &&
       model.upperPositionLimit.size() == static_cast<size_t>(dof))
    {
        for (int i = 0; i < dof; i++) {
            bounds.setLow(i, model.lowerPositionLimit[i]);
            bounds.setHigh(i, model.upperPositionLimit[i]);
        }
    }
    else {
        // If joint limits are not defined, use default bounds.
        for (int i = 0; i < dof; i++) {
            bounds.setLow(i, -3.14);
            bounds.setHigh(i,  3.14);
        }
    }
    space->setBounds(bounds);

    // Set up the OMPL SimpleSetup object.
    simple_setup_ = std::make_shared<og::SimpleSetup>(space);

    // Set the state validity checker. This lambda converts the OMPL state into an Eigen::VectorXd.
    simple_setup_->setStateValidityChecker([this, dof](const ob::State *state) {
        const auto *stateVals = state->as<ob::RealVectorStateSpace::StateType>()->values;
        Eigen::VectorXd q(dof);
        for (int i = 0; i < dof; i++) {
            q[i] = stateVals[i];
        }
        return robot_model_->isStateValid(q);
    });
}

bool MotionPlanner::plan(const Eigen::VectorXd &start, const Eigen::VectorXd &goal, double planningTime)
{
    int dof = robot_model_->getDOF();
    if(start.size() != dof || goal.size() != dof) {
        std::cerr << "Start or goal state does not match robot DOF." << std::endl;
        return false;
    }
    
    // Set start and goal states.
    ob::ScopedState<> startState(simple_setup_->getStateSpace());
    ob::ScopedState<> goalState(simple_setup_->getStateSpace());
    for (int i = 0; i < dof; i++) {
        startState->as<ob::RealVectorStateSpace::StateType>()->values[i] = start[i];
        goalState->as<ob::RealVectorStateSpace::StateType>()->values[i] = goal[i];
    }
    
    simple_setup_->setStartAndGoalStates(startState, goalState);
    
    // Use the RRTConnect planner from the ompl::geometric namespace.
    auto planner = std::make_shared<og::RRTConnect>(simple_setup_->getSpaceInformation());
    simple_setup_->setPlanner(planner);
    
    // Attempt to solve the planning problem.
    ob::PlannerStatus solved = simple_setup_->solve(planningTime);
    if (solved) {
        std::cout << "Found solution:" << std::endl;
        simple_setup_->getSolutionPath().printAsMatrix(std::cout);
        return true;
    } else {
        std::cout << "No solution found." << std::endl;
        return false;
    }
}

og::PathGeometric MotionPlanner::getSolutionPath() const
{
    return simple_setup_->getSolutionPath();
}

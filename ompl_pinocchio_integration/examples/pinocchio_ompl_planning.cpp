#include <string>
#include <Eigen/Dense>
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <memory>
#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <iostream>
#include <ompl/geometric/planners/rrt/RRTConnect.h>
#include <random>

// Forward declaration of RobotModel so that MotionPlanner can refer to it.
class RobotModel;

namespace og = ompl::geometric;
namespace ob = ompl::base;

//---------------------------------------------------------------------------
// MotionPlanner class declaration
//---------------------------------------------------------------------------
class MotionPlanner {
public:
    /// Constructor that takes a pointer to a RobotModel.
    MotionPlanner(RobotModel* robot_model);

    /// Plan a motion from start to goal in the robot's configuration space.
    bool plan(const Eigen::VectorXd &start, const Eigen::VectorXd &goal, double planningTime = 5.0);

    /// Retrieve the solution path if one was found.
    og::PathGeometric getSolutionPath() const;

private:
    RobotModel* robot_model_;
    std::shared_ptr<og::SimpleSetup> simple_setup_;
};

//---------------------------------------------------------------------------
// RobotModel class declaration
//---------------------------------------------------------------------------
class RobotModel {
public:
    /// Constructor that loads the robot model from a URDF file.
    RobotModel(const std::string &urdf_path);

    /// Compute forward kinematics for a given joint configuration q.
    void computeForwardKinematics(const Eigen::VectorXd &q);

    /// Check whether the given state is valid (e.g., within joint limits).
    bool isStateValid(const Eigen::VectorXd &q);

    /// Returns the number of degrees of freedom.
    int getDOF() const { return model_.nq; }

    /// Get a const reference to the Pinocchio model.
    const pinocchio::Model& getModel() const { return model_; }

private:
    pinocchio::Model model_;
    pinocchio::Data data_;
};

//---------------------------------------------------------------------------
// RobotModel implementations
//---------------------------------------------------------------------------

RobotModel::RobotModel(const std::string &urdf_path)
{
    try {
        // Build the model from a URDF file.
        pinocchio::urdf::buildModel(urdf_path, model_);
        data_ = pinocchio::Data(model_);
        std::cout << "Loaded robot model from: " << urdf_path << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error loading robot model: " << e.what() << std::endl;
        throw;
    }
}

void RobotModel::computeForwardKinematics(const Eigen::VectorXd &q)
{
    if(q.size() != model_.nq) {
        std::cerr << "Error: q vector size (" << q.size() 
                  << ") does not match robot dof (" << model_.nq << ")" << std::endl;
        return;
    }
    // Compute forward kinematics and update placements.
    pinocchio::forwardKinematics(model_, data_, q);
    pinocchio::updateGlobalPlacements(model_, data_);
}

bool RobotModel::isStateValid(const Eigen::VectorXd &q)
{
    if(q.size() != model_.nq)
    {
        std::cerr << "Invalid state dimension: " << q.size() 
                  << " vs expected " << model_.nq << std::endl;
        return false;
    }
    
    // If joint limits are defined, check that q is within them.
    if(model_.lowerPositionLimit.size() == static_cast<size_t>(model_.nq) &&
       model_.upperPositionLimit.size() == static_cast<size_t>(model_.nq))
    {
        for(int i = 0; i < q.size(); i++)
        {
            if(q[i] < model_.lowerPositionLimit[i] || q[i] > model_.upperPositionLimit[i])
                return false;
        }
    }
    
    // Additional checks (e.g., collision or singularity) can be added here.
    return true;
}

//---------------------------------------------------------------------------
// MotionPlanner implementations
//---------------------------------------------------------------------------

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

    // Set the state validity checker.
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
    
    // Use the RRTConnect planner.
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

//---------------------------------------------------------------------------
// Helper function to generate a random goal configuration
//---------------------------------------------------------------------------

Eigen::VectorXd generateRandomGoal(const RobotModel &robot) {
    int dof = robot.getDOF();
    Eigen::VectorXd goal(dof);
    const pinocchio::Model &model = robot.getModel();

    // Setup a random number generator.
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // If joint limits are defined, sample between them.
    if(model.lowerPositionLimit.size() == static_cast<size_t>(dof) &&
       model.upperPositionLimit.size() == static_cast<size_t>(dof)) {
        for (int i = 0; i < dof; i++) {
            std::uniform_real_distribution<double> dist(model.lowerPositionLimit[i],
                                                          model.upperPositionLimit[i]);
            goal[i] = dist(gen);
        }
    } else {
        // Otherwise, use a default range.
        for (int i = 0; i < dof; i++) {
            std::uniform_real_distribution<double> dist(-3.14, 3.14);
            goal[i] = dist(gen);
        }
    }
    return goal;
}

//---------------------------------------------------------------------------
// Main function
//---------------------------------------------------------------------------

int main(int argc, char** argv)
{
    if(argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_urdf>" << std::endl;
        return -1;
    }
    
    std::string urdf_path = argv[1];
    
    // Load the robot model.
    RobotModel robot(urdf_path);
    
    // Define the start configuration as a zero vector.
    //int dof = robot.getDOF();
    Eigen::VectorXd start = generateRandomGoal(robot);
    // Print the generated goal.
    std::cout << "Random start configuration: " << start.transpose() << std::endl;

    // Generate a random goal configuration.
    Eigen::VectorXd goal = generateRandomGoal(robot);
    
    // Print the generated goal.
    std::cout << "Random goal configuration: " << goal.transpose() << std::endl;
    
    // Create the motion planner.
    MotionPlanner planner(&robot);
    
    // Run the planner with a maximum planning time of 5 seconds.
    if(planner.plan(start, goal, 5.0)) {
        std::cout << "Motion planning succeeded!" << std::endl;
    } else {
        std::cout << "Motion planning failed." << std::endl;
    }
    
    return 0;
}

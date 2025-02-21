#include "Robot_Model.hpp"
#include "Motion_Planner.hpp"
#include <Eigen/Dense>
#include <iostream>
#include <random>

// Helper function to generate a random goal configuration
Eigen::VectorXd generateRandomGoal(const RobotModel &robot) {
    int dof = robot.getDOF();
    Eigen::VectorXd goal(dof);
    const pinocchio::Model &model = robot.getModel();

    // Setup a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    // Check if joint limits are defined
    if(model.lowerPositionLimit.size() == static_cast<size_t>(dof) &&
       model.upperPositionLimit.size() == static_cast<size_t>(dof)) {
        for (int i = 0; i < dof; i++) {
            // Create a uniform distribution between the lower and upper bound for each joint
            std::uniform_real_distribution<double> dist(model.lowerPositionLimit[i],
                                                          model.upperPositionLimit[i]);
            goal[i] = dist(gen);
        }
    } else {
        // Use a default range if joint limits are not available.
        for (int i = 0; i < dof; i++) {
            std::uniform_real_distribution<double> dist(-3.14, 3.14);
            goal[i] = dist(gen);
        }
    }
    return goal;
}

int main(int argc, char** argv)
{
    if(argc < 2) {
        std::cerr << "Usage: robot_planner <path_to_urdf>" << std::endl;
        return -1;
    }
    
    std::string urdf_path = argv[1];
    
    // Load the robot model using Pinocchio.
    RobotModel robot(urdf_path);
    
    // Define the start configuration as a zero vector.
    int dof = robot.getDOF();
    Eigen::VectorXd start = Eigen::VectorXd::Zero(dof);
    
    // Generate a random goal configuration.
    Eigen::VectorXd goal = generateRandomGoal(robot);
    
    // Print the generated goal configuration.
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

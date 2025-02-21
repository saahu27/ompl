#include "Robot_Model.hpp"
#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/kinematics.hpp>
#include <iostream>

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

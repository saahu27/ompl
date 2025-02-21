#ifndef ROBOT_MODEL_HPP
#define ROBOT_MODEL_HPP

#include <string>
#include <Eigen/Dense>
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>

class RobotModel {
public:
    /// Constructor that loads the robot model from a URDF file.
    RobotModel(const std::string &urdf_path);

    /// Compute forward kinematics for a given joint configuration q.
    void computeForwardKinematics(const Eigen::VectorXd &q);

    /// Check whether the given state is valid (e.g. within joint limits).
    bool isStateValid(const Eigen::VectorXd &q);

    /// Returns the number of degrees of freedom.
    int getDOF() const { return model_.nq; }

    /// Get a const reference to the Pinocchio model.
    const pinocchio::Model& getModel() const { return model_; }

private:
    pinocchio::Model model_;
    pinocchio::Data data_;
};

#endif // ROBOT_MODEL_HPP

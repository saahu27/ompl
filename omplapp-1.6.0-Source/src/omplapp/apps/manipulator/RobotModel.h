#ifndef ROBOT_MODEL_H
#define ROBOT_MODEL_H

#include <string>
#include <vector>
#include <memory>
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>
#include <Eigen/Dense>

// FCL – using double precision
#include <fcl/fcl.h>

// Structure to hold a link’s collision geometry.
struct LinkCollision {
    std::string linkName;
    std::shared_ptr<fcl::CollisionObjectd> collisionObject;
};

class RobotModel {
public:
    /// Load a robot model from a URDF file.
    RobotModel(const std::string &urdf_path);

    /// Compute forward kinematics for joint configuration q.
    void computeForwardKinematics(const Eigen::VectorXd &q);

    /// Check that q is within joint limits.
    bool isStateValid(const Eigen::VectorXd &q) const;

    /// Return the robot’s degrees of freedom.
    int getDOF() const { return model_.nq; }

    /// Get the Pinocchio model.
    const pinocchio::Model& getModel() const { return model_; }
    /// Get the Pinocchio data (for forward kinematics).
    pinocchio::Data& getData() { return data_; }

    /// Add collision geometry for a given link by specifying the link name and mesh file.
    bool addLinkCollisionMesh(const std::string &linkName, const std::string &meshFile);

    /// Retrieve all link collision objects.
    const std::vector<LinkCollision>& getLinkCollisions() const { return linkCollisions_; }

private:
    pinocchio::Model model_;
    pinocchio::Data data_;

    std::vector<LinkCollision> linkCollisions_;

    /// Utility: load a mesh from file (using Assimp) and build an FCL BVH model,
    /// then wrap it in a CollisionObject.
    std::shared_ptr<fcl::CollisionObjectd> buildCollisionObjectFromMesh(const std::string &meshFile);
};

#endif // ROBOT_MODEL_H

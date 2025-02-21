#include "PinocchioManipulatorPlanning.h"
#include "PinocchioManipulatorStateValidityChecker.h"
#include "ompl/base/ScopedState.h"
#include <ompl/util/Exception.h>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <pinocchio/algorithm/kinematics.hpp>
#include <pinocchio/algorithm/frames.hpp>
#include <Eigen/Dense>

using namespace ompl::app;

bool PinocchioManipulatorPlanning::initialize()
{
    try {
        // Build the Pinocchio model from the URDF.
        pinocchio::urdf::buildModel(urdfFile_, model_, false);
        data_ = pinocchio::Data(model_);
        dof_ = model_.nq;  // Set number of joints.

        // Create a new state space with dimension equal to dof_.
        stateSpace_ = std::make_shared<ompl::base::RealVectorStateSpace>(dof_);
        ompl::base::RealVectorBounds bounds(dof_);
        // In production, extract joint limits from the URDF.
        for (unsigned int i = 0; i < dof_; ++i) {
            bounds.setLow(i, -3.14159);
            bounds.setHigh(i,  3.14159);
        }
        stateSpace_->as<ompl::base::RealVectorStateSpace>()->setBounds(bounds);

        // Parse collision geometry.
        if (!parseCollisionGeometry()) {
            std::cerr << "Failed to parse collision geometry." << std::endl;
            return false;
        }

        // Setup the state validity checker.
        setupStateValidityChecker();

        return true;
    } catch (const std::exception &ex) {
        std::cerr << "Exception in initialize: " << ex.what() << std::endl;
        return false;
    }
}

bool PinocchioManipulatorPlanning::parseCollisionGeometry()
{
    // For production, parse the URDF collision elements.
    // Here we loop over each link name and try to load "meshes/<linkName>_collision.stl".
    const std::string meshPath = "meshes/";
    Assimp::Importer importer;
    for (const std::string &linkName : model_.names) {
        std::string collisionFile = meshPath + linkName + "_collision.stl";
        const aiScene *scene = importer.ReadFile(collisionFile,
                                                  aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
        if (!scene || !scene->HasMeshes()) {
            std::cerr << "Warning: No collision mesh found for link: " << linkName << std::endl;
            continue;
        }
        // For demonstration, create a placeholder FCL collision object (a small box).
        std::shared_ptr<::fcl::CollisionObjectd> colObj;
        ::fcl::Boxd box(0.1, 0.1, 0.1); // placeholder dimensions
        colObj = std::make_shared<::fcl::CollisionObjectd>(std::make_shared<::fcl::Boxd>(box));
        linkCollisionObjects_.push_back(colObj);
        linkCollisionScenes_.push_back(scene); // for visualization
    }
    return true;
}

void PinocchioManipulatorPlanning::setupStateValidityChecker()
{
    // Create and install our custom state validity checker.
    auto svc = std::make_shared<PinocchioStateValidityChecker>(getSpaceInformation(), *this);
    getSpaceInformation()->setStateValidityChecker(svc);
}

bool PinocchioManipulatorPlanning::isSelfCollisionEnabled() const
{
    return true;
}

ompl::base::ScopedState<> PinocchioManipulatorPlanning::getDefaultStartState() const
{
    // Create a state in the current state space.
    ompl::base::ScopedState<ompl::base::RealVectorStateSpace> state(stateSpace_);
    for (unsigned int i = 0; i < dof_; ++i)
        state[i] = 0.0;
    return state;
}

ompl::base::ScopedState<> PinocchioManipulatorPlanning::getFullStateFromGeometricComponent(const ompl::base::ScopedState<> &state) const
{
    // For a manipulator, the full state is simply the joint angles.
    return state;
}

const ompl::base::StateSpacePtr& PinocchioManipulatorPlanning::getGeometricComponentStateSpace() const
{
    return stateSpace_;
}

unsigned int PinocchioManipulatorPlanning::getRobotCount() const
{
    return 1;
}

void PinocchioManipulatorPlanning::updateLinkCollisionObjects(const ompl::base::State *state)
{
    // Convert the OMPL state (joint angles) into an Eigen vector.
    Eigen::VectorXd q_eigen(dof_);
    const auto *rvState = state->as<ompl::base::RealVectorStateSpace::StateType>();
    for (unsigned int i = 0; i < dof_; ++i)
        q_eigen[i] = rvState->values[i];

    // Compute forward kinematics.
    pinocchio::forwardKinematics(model_, data_, q_eigen);
    pinocchio::updateFramePlacements(model_, data_);

    // Update each collision object using the computed transforms.
    for (size_t i = 0; i < linkCollisionObjects_.size(); ++i) {
        // Convert the Pinocchio SE3 (data_.oMf[i]) to an Eigen::Isometry3d.
        // Use toHomogeneousMatrix() to get the 4x4 matrix.
        Eigen::Isometry3d tf(data_.oMf[i].toHomogeneousMatrix());
        ::fcl::Transform3d fclTf(tf.matrix());
        linkCollisionObjects_[i]->setTransform(fclTf);
        linkCollisionObjects_[i]->computeAABB();
    }
}

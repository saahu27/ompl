#ifndef OMPLAPP_MANIPULATOR_PLANNING_
#define OMPLAPP_MANIPULATOR_PLANNING_

#include "omplapp/apps/AppBase.h"

// Pinocchio headers
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>

// Standard headers
#include <string>
#include <vector>

// OMPL base headers
#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/base/ScopedState.h>
#include <ompl/base/StateSpace.h>

namespace ompl
{
  namespace app
  {

    // A simple struct to hold both translation and rotation offset.
    struct LinkOffset
    {
      aiVector3D translation;      // translation offset from URDF <origin xyz="..."/>
      Eigen::Quaterniond rotation; // rotation offset from URDF <origin rpy="..."/>
    };

    /**
       \brief A planning class for manipulators that loads a URDF via Pinocchio.
       
       The planning state space is the joint space (a RealVectorStateSpace whose dimension equals
       the number of joints). The overridden setRobotMesh(…) method detects URDF files and uses Pinocchio 
       to build the robot model and extract (simulated) collision geometry for each link. The custom 
       geometric state extractor computes forward kinematics (via Pinocchio) so that collision checking 
       and visualization use the individual link transforms.
    */
    class ManipulatorPlanning : public AppBase<AppType::GEOMETRIC>
    {
    public:
      ManipulatorPlanning();
      virtual ~ManipulatorPlanning() = default;

      /// Override to load a URDF using Pinocchio and then build collision geometry.
      virtual bool setRobotMesh(const std::string &robot) override;

      /// Return the center for the given link.
      /// (We override this to use our locally stored collision shifts rather than the base class implementation.)
      virtual aiVector3D getRobotCenter(unsigned int robotIndex) const ;

      virtual ompl::base::RealVectorBounds inferEnvironmentBounds() const;

      /// Provide a default start state.
      virtual ompl::base::ScopedState<> getDefaultStartState() const override;

      /// Return a lambda that computes the forward kinematics for a given collision body.
      virtual GeometricStateExtractor getGeometricStateExtractor() const;

      /// The planning state space is the joint space.
      virtual const ompl::base::StateSpacePtr& getGeometricComponentStateSpace() const override;

      virtual const GeometrySpecification& getGeometrySpecification() const;

      /// Return the number of collision bodies (links) in the robot.
      virtual unsigned int getRobotCount() const override;

      /// Pure virtual functions from AppBase.
      virtual bool isSelfCollisionEnabled() const override;
      virtual ompl::base::ScopedState<> getFullStateFromGeometricComponent(
          const ompl::base::ScopedState<> &state) const override;
      
      virtual const ompl::base::StateSpacePtr& getStateSpace() const { return jointSpace_; }

    protected:
      /// Compute the SE3 pose of the link with index linkIndex.
      ompl::base::ScopedState<> computeLinkPose(const ompl::base::State* state,
                                                unsigned int linkIndex) const;

      /// For our manipulator, the geometric component of the state is computed on the fly.
      virtual const ompl::base::State* getGeometricComponentStateInternal(
          const ompl::base::State* state, unsigned int index) const override;

      // Pinocchio model and data.
      pinocchio::Model pinModel_;
      mutable pinocchio::Data pinData_;

      // Number of joints.
      unsigned int nJoints_;

      // For each collision body (link) from the URDF, store its frame id.
      std::vector<unsigned int> collisionLinkIndices_;

      // Our local copy of the joint (planning) state space.
      ompl::base::StateSpacePtr jointSpace_;

      // GeometrySpecification (we use this single member consistently).
      GeometrySpecification geom_;

      // Geometric state space for rendering (an SE3 space).
      ompl::base::StateSpacePtr geomSpace_;
    };

  }
}

#endif

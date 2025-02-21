#ifndef OMPLAPP_PINOCCHIO_MANIPULATOR_PLANNING_
#define OMPLAPP_PINOCCHIO_MANIPULATOR_PLANNING_

// Include FCL headers first so that the global ::fcl namespace is defined.
#include <fcl/fcl.h>

// OMPL.app headers
#include "omplapp/apps/AppBase.h"
#include "omplapp/geometry/RigidBodyGeometry.h"

// Pinocchio headers
#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/multibody/model.hpp>
#include <pinocchio/multibody/data.hpp>

// We need RealVectorStateSpace (make sure your OMPL include paths are set correctly)
#include <ompl/base/spaces/RealVectorStateSpace.h>

#include <vector>
#include <string>
#include <memory>

// Forward declaration of our custom state validity checker.
namespace ompl { namespace app { class PinocchioStateValidityChecker; } }

namespace ompl {
namespace app {

/** \brief A planning application for an n-dof manipulator using Pinocchio.
    This class derives from OMPL.app’s AppBase (GEOMETRIC) and integrates with the
    RigidBodyGeometry framework. It loads a URDF using Pinocchio, constructs a joint
    space, loads collision geometry via Assimp, builds FCL collision objects (using an FCL
    wrapper), and overrides necessary methods so that environment bound inference and
    visualization work seamlessly.
*/
class PinocchioManipulatorPlanning : public AppBase<AppType::GEOMETRIC>
{
public:
    /// \brief Constructor.
    /// Since the state space dimension is not known until after parsing the URDF, we pass a dummy state space of dimension 1.
    PinocchioManipulatorPlanning(const std::string &urdfFile,
                                 const std::string &baseLink,
                                 const std::string &tipLink)
      : AppBase<AppType::GEOMETRIC>(std::make_shared<ompl::base::RealVectorStateSpace>(1), Motion_3D),
        urdfFile_(urdfFile), baseLink_(baseLink), tipLink_(tipLink), dof_(1) // dummy dof
    {
    }

    virtual ~PinocchioManipulatorPlanning() {}

    /// \brief Initialize the planning application:
    /// - Build the Pinocchio model from the URDF.
    /// - Create the correct state space (with dimension = number of joints).
    /// - Parse collision geometry.
    /// - Install the state validity checker.
    bool initialize();

    // Overridden methods from AppBase.
    bool isSelfCollisionEnabled() const override;
    ompl::base::ScopedState<> getDefaultStartState() const override;
    ompl::base::ScopedState<> getFullStateFromGeometricComponent(const ompl::base::ScopedState<> &state) const override;
    const ompl::base::StateSpacePtr& getGeometricComponentStateSpace() const override;
    unsigned int getRobotCount() const override;

    // Provide an accessor to the underlying SimpleSetup.
    ompl::geometric::SimpleSetup* getSimpleSetup() { return this; }
    const ompl::geometric::SimpleSetup* getSimpleSetup() const { return this; }

    // Accessors for Pinocchio model and data.
    const pinocchio::Model& getPinocchioModel() const { return model_; }
    pinocchio::Data& getPinocchioData() { return data_; }

    // Get the FCL collision objects corresponding to each link.
    const std::vector<std::shared_ptr<::fcl::CollisionObjectd>>& getLinkCollisionObjects() const { return linkCollisionObjects_; }

    /// \brief Update each link’s collision object using forward kinematics computed by Pinocchio.
    void updateLinkCollisionObjects(const ompl::base::State *state);

protected:
    /// \brief Parse collision geometry for each link.
    /// In production this would parse the collision elements from the URDF.
    /// Here, we assume collision meshes are in "meshes/<linkName>_collision.stl".
    bool parseCollisionGeometry();

    /// \brief Setup our custom state validity checker.
    virtual void setupStateValidityChecker();

    // Implementation of pure virtual from AppBase.
    virtual const ompl::base::State* getGeometricComponentStateInternal(const ompl::base::State* state, unsigned int index) const override
    {
        (void)index; // Only one component exists.
        return state;
    }

    // Pinocchio model and data.
    pinocchio::Model model_;
    pinocchio::Data data_;

    // URDF file and link names.
    std::string urdfFile_;
    std::string baseLink_;
    std::string tipLink_;

    // Number of degrees of freedom.
    unsigned int dof_;

    // FCL collision objects for each link.
    std::vector<std::shared_ptr<::fcl::CollisionObjectd>> linkCollisionObjects_;

    // Optionally store Assimp scenes for visualization.
    std::vector<const aiScene*> linkCollisionScenes_;

    // The state space (joint space).
    ompl::base::StateSpacePtr stateSpace_;
};

} // namespace app
} // namespace ompl

#endif

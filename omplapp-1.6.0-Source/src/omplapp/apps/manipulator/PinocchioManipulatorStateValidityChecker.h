#ifndef OMPLAPP_PINOCCHIO_STATE_VALIDITY_CHECKER_
#define OMPLAPP_PINOCCHIO_STATE_VALIDITY_CHECKER_

#include <ompl/base/StateValidityChecker.h>
#include "PinocchioManipulatorPlanning.h"

namespace ompl {
namespace app {

/** \brief Custom state validity checker that uses the FCL wrapper.
    It updates collision objects using Pinocchio forward kinematics and then uses the FCL wrapper to check for collisions.
*/
class PinocchioStateValidityChecker : public ompl::base::StateValidityChecker
{
public:
    PinocchioStateValidityChecker(const ompl::base::SpaceInformationPtr &si,
                                  const PinocchioManipulatorPlanning &app);
    virtual ~PinocchioStateValidityChecker() = default;

    // Check whether the given state is collision free.
    bool isValid(const ompl::base::State *state) const override;

    // (Optional) Continuous collision checking overload.
    bool isValid(const ompl::base::State *s1, const ompl::base::State *s2, double &collisionTime) const;

protected:
    const PinocchioManipulatorPlanning &app_;
};

} // namespace app
} // namespace ompl

#endif

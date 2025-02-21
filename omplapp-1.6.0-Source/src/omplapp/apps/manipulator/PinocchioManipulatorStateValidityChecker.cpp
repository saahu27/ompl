#include "PinocchioManipulatorStateValidityChecker.h"
#include <fcl/narrowphase/collision.h>
#include <iostream>

using namespace ompl::app;

PinocchioStateValidityChecker::PinocchioStateValidityChecker(
    const ompl::base::SpaceInformationPtr &si,
    const PinocchioManipulatorPlanning &app)
  : ompl::base::StateValidityChecker(si), app_(app)
{
}

bool PinocchioStateValidityChecker::isValid(const ompl::base::State *state) const
{
    if (!si_->satisfiesBounds(state))
        return false;

    // Update collision objects using Pinocchio.
    const_cast<PinocchioManipulatorPlanning&>(app_).updateLinkCollisionObjects(state);

    fcl::CollisionRequestd request;
    fcl::CollisionResultd result;

    // Create a dummy environment collision object (a large box).
    std::shared_ptr<::fcl::CollisionObjectd> envObj;
    {
        ::fcl::Boxd envBox(5.0, 5.0, 5.0);
        envObj = std::make_shared<::fcl::CollisionObjectd>(std::make_shared<::fcl::Boxd>(envBox));
    }

    // Check each link against the environment.
    for (const auto &linkObj : app_.getLinkCollisionObjects()) {
        result = fcl::CollisionResultd();
        if (fcl::collide(linkObj.get(), envObj.get(), request, result) > 0)
            return false;
    }

    // Check self-collision.
    const auto &linkObjs = app_.getLinkCollisionObjects();
    for (size_t i = 0; i < linkObjs.size(); ++i) {
        for (size_t j = i + 1; j < linkObjs.size(); ++j) {
            result = fcl::CollisionResultd();
            if (fcl::collide(linkObjs[i].get(), linkObjs[j].get(), request, result) > 0)
                return false;
        }
    }
    return true;
}

bool PinocchioStateValidityChecker::isValid(const ompl::base::State *s1,
                                              const ompl::base::State *s2,
                                              double &collisionTime) const
{
    // For simplicity, we return the discrete validity of s1.
    collisionTime = 0.0;
    return isValid(s1);
}

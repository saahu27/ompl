#ifndef PLANNER_REGISTRY_H
#define PLANNER_REGISTRY_H

#include <map>
#include <string>
#include <functional>
#include <memory>
#include <ompl/base/Planner.h>
#include <ompl/base/SpaceInformation.h>

// Define a namespace alias for brevity.
namespace ob = ompl::base;

namespace ompl
{
  namespace geometric
  {
    /// A simple registry for geometric planners.
    class PlannerRegistry
    {
    public:
      using PlannerFactory = std::function<ob::PlannerPtr(ob::SpaceInformationPtr)>;

      static PlannerRegistry &getInstance()
      {
        static PlannerRegistry instance;
        return instance;
      }

      void registerPlanner(const std::string &name, PlannerFactory factory)
      {
        planners_[name] = factory;
      }

      const std::map<std::string, PlannerFactory> &getPlanners() const
      {
        return planners_;
      }

    private:
      PlannerRegistry() = default;
      std::map<std::string, PlannerFactory> planners_;
    };
  } // namespace geometric

  namespace control
  {
    /// A simple registry for control planners.
    class PlannerRegistry
    {
    public:
      using PlannerFactory = std::function<ob::PlannerPtr(ob::SpaceInformationPtr)>;

      static PlannerRegistry &getInstance()
      {
        static PlannerRegistry instance;
        return instance;
      }

      void registerPlanner(const std::string &name, PlannerFactory factory)
      {
        planners_[name] = factory;
      }

      const std::map<std::string, PlannerFactory> &getPlanners() const
      {
        return planners_;
      }

    private:
      PlannerRegistry() = default;
      std::map<std::string, PlannerFactory> planners_;
    };
  } // namespace control
}

#endif // PLANNER_REGISTRY_H

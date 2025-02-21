#include <pinocchio/fwd.hpp>
#include "PlannerRegistry.h"
#include <ompl/util/Console.h>

// Geometric planners
#include <ompl/geometric/planners/rrt/RRTstar.h>
#include <ompl/geometric/planners/rrt/LBTRRT.h>
#include <ompl/geometric/planners/rrt/TRRT.h>
#include <ompl/geometric/planners/rrt/RRTConnect.h>
#include <ompl/geometric/planners/rrt/BiTRRT.h>
#include <ompl/geometric/planners/rrt/LazyLBTRRT.h>
#include <ompl/geometric/planners/rrt/pRRT.h>
//#include <ompl/geometric/planners/rrt/TSRRT.h>   // Cannot register: requires 2 arguments
//#include <ompl/geometric/planners/rrt/VFRRT.h>    // Cannot register: requires 5 arguments
#include <ompl/geometric/planners/rrt/STRRTstar.h>
#include <ompl/geometric/planners/rrt/SORRTstar.h>
#include <ompl/geometric/planners/rrt/RRTXstatic.h>
#include <ompl/geometric/planners/kpiece/KPIECE1.h>
#include <ompl/geometric/planners/kpiece/BKPIECE1.h>
#include <ompl/geometric/planners/kpiece/LBKPIECE1.h>
#include <ompl/geometric/planners/pdst/PDST.h>
#include <ompl/geometric/planners/prm/PRM.h>
#include <ompl/geometric/planners/prm/PRMstar.h>
#include <ompl/geometric/planners/prm/LazyPRM.h>
#include <ompl/geometric/planners/prm/LazyPRMstar.h>
#include <ompl/geometric/planners/prm/SPARS.h>
#include <ompl/geometric/planners/prm/SPARStwo.h>
#include <ompl/geometric/planners/sbl/SBL.h>
#include <ompl/geometric/planners/sbl/pSBL.h>
#include <ompl/geometric/planners/est/EST.h>
#include <ompl/geometric/planners/est/BiEST.h>
#include <ompl/geometric/planners/informedtrees/AITstar.h>
#include <ompl/geometric/planners/informedtrees/ABITstar.h>
#include <ompl/geometric/planners/informedtrees/BITstar.h>

// Control planners
#include <ompl/control/planners/kpiece/KPIECE1.h>
#include <ompl/control/planners/rrt/RRT.h>
#include <ompl/control/planners/est/EST.h>
#include <ompl/control/planners/sst/SST.h>
#include <ompl/control/planners/syclop/SyclopEST.h>
#include <ompl/control/planners/syclop/SyclopRRT.h> 

namespace ob = ompl::base;

// Register all geometric planners.
void registerGeometricPlanners()
{
    auto &geoRegistry = ompl::geometric::PlannerRegistry::getInstance();

    geoRegistry.registerPlanner("AITstar", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::AITstar>(si);
    });

    geoRegistry.registerPlanner("ABITstar", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::ABITstar>(si);
    });

    geoRegistry.registerPlanner("BITstar", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::BITstar>(si);
    });

    geoRegistry.registerPlanner("RRTstar", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::RRTstar>(si);
    });
    geoRegistry.registerPlanner("KPIECE1", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::KPIECE1>(si);
    });
    geoRegistry.registerPlanner("LBTRRT", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::LBTRRT>(si);
    });
    geoRegistry.registerPlanner("TRRT", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::TRRT>(si);
    });
    geoRegistry.registerPlanner("RRTConnect", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::RRTConnect>(si);
    });
    geoRegistry.registerPlanner("BiTRRT", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::BiTRRT>(si);
    });
    geoRegistry.registerPlanner("LazyLBTRRT", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::LazyLBTRRT>(si);
    });
    geoRegistry.registerPlanner("pRRT", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::pRRT>(si);
    });
    // Skip TSRRT and VFRRT because they require additional parameters.
    geoRegistry.registerPlanner("STRRTstar", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::STRRTstar>(si);
    });
    geoRegistry.registerPlanner("SORRTstar", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::SORRTstar>(si);
    });
    geoRegistry.registerPlanner("RRTXstatic", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::RRTXstatic>(si);
    });
    geoRegistry.registerPlanner("BKPIECE1", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::BKPIECE1>(si);
    });
    geoRegistry.registerPlanner("LBKPIECE1", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::LBKPIECE1>(si);
    });
    geoRegistry.registerPlanner("PDST", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::PDST>(si);
    });
    geoRegistry.registerPlanner("PRM", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::PRM>(si);
    });
    geoRegistry.registerPlanner("PRMstar", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::PRMstar>(si);
    });
    geoRegistry.registerPlanner("LazyPRM", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::LazyPRM>(si);
    });
    geoRegistry.registerPlanner("LazyPRMstar", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::LazyPRMstar>(si);
    });
    geoRegistry.registerPlanner("SPARS", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::SPARS>(si);
    });
    geoRegistry.registerPlanner("SPARStwo", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::SPARStwo>(si);
    });
    geoRegistry.registerPlanner("SBL", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::SBL>(si);
    });
    geoRegistry.registerPlanner("pSBL", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::pSBL>(si);
    });
    geoRegistry.registerPlanner("EST", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::EST>(si);
    });
    geoRegistry.registerPlanner("BiEST", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      return std::make_shared<ompl::geometric::BiEST>(si);
    });
}

// Register all control planners.
void registerControlPlanners()
{
    auto &ctrlRegistry = ompl::control::PlannerRegistry::getInstance();

    ctrlRegistry.registerPlanner("KPIECE1", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      auto ctrlSI = std::static_pointer_cast<ompl::control::SpaceInformation>(si);
      return std::make_shared<ompl::control::KPIECE1>(ctrlSI);
    });
    ctrlRegistry.registerPlanner("RRT", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      auto ctrlSI = std::static_pointer_cast<ompl::control::SpaceInformation>(si);
      return std::make_shared<ompl::control::RRT>(ctrlSI);
    });
    ctrlRegistry.registerPlanner("EST", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      auto ctrlSI = std::static_pointer_cast<ompl::control::SpaceInformation>(si);
      return std::make_shared<ompl::control::EST>(ctrlSI);
    });
    ctrlRegistry.registerPlanner("SST", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
      auto ctrlSI = std::static_pointer_cast<ompl::control::SpaceInformation>(si);
      return std::make_shared<ompl::control::SST>(ctrlSI);
    });
    // ctrlRegistry.registerPlanner("SyclopEST", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
    //   auto ctrlSI = std::static_pointer_cast<ompl::control::SpaceInformation>(si);
    //   return std::make_shared<ompl::control::SyclopEST>(ctrlSI);
    // });
    // ctrlRegistry.registerPlanner("SyclopRRT", [](ob::SpaceInformationPtr si) -> ob::PlannerPtr {
    //   auto ctrlSI = std::static_pointer_cast<ompl::control::SpaceInformation>(si);
    //   return std::make_shared<ompl::control::SyclopRRT>(ctrlSI);
    // });
    // Skip Syclop because it is abstract.
}

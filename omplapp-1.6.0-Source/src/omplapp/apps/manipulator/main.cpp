#include "PinocchioManipulatorPlanning.h"
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/rrt/RRTConnect.h>
#include <ompl/config.h>
#include <iostream>

using namespace ompl;

int main(int argc, char **argv)
{
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <URDF file> <base link> <tip link>" << std::endl;
        return 1;
    }
    std::string urdfFile(argv[1]);
    std::string baseLink(argv[2]);
    std::string tipLink(argv[3]);

    // Create the planning application.
    app::PinocchioManipulatorPlanning app(urdfFile, baseLink, tipLink);

    if (!app.initialize()) {
        std::cerr << "Failed to initialize PinocchioManipulatorPlanning." << std::endl;
        return 1;
    }

    // Setup the planning problem.
    app.setup();

    // Create and set a planner (RRTConnect).
    auto planner = std::make_shared<ompl::geometric::RRTConnect>(app.getSpaceInformation());
    app.getSimpleSetup()->setPlanner(planner);

    // Solve for a collision-free path.
    ompl::base::PlannerStatus solved = app.getSimpleSetup()->solve(5.0);

    if (solved) {
        std::cout << "Found solution:" << std::endl;
        app.getSimpleSetup()->getSolutionPath().printAsMatrix(std::cout);
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}

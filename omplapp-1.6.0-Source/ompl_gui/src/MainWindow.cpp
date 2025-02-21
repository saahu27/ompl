#include "MainWindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <ompl/base/objectives/PathLengthOptimizationObjective.h>
#include <ompl/util/Console.h>

using namespace ompl;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), 
        timeLimitValue(10.0), 
        isGeometric(true), 
        is3D(true),
        planner_(nullptr),
        solution_(nullptr) // PlannerSolution requires a path object 
{
    omplSetup_ = std::make_shared<ompl::app::SE3RigidBodyPlanning>();

    createActions();
    createMenus();
    createRobotTypeList();

    // Create the mainWidget with the robotTypes_ list
    mainWidget_ = new MainWidget(robotTypes, this);
    // Set it as the central widget
    setCentralWidget(mainWidget_);

    setWindowTitle("OMPL.app (C++)");
    resize(1024, 768);


    connect(mainWidget_->problemWidget->robotTypeSelect,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::setRobotType);


    connect(mainWidget_->solveWidget->solveButton, &QPushButton::clicked,
            this, &MainWindow::solve);


    connect(mainWidget_->solveWidget->clearButton, &QPushButton::clicked,
            this, [this]() { clear(true); });


    connect(mainWidget_->boundsWidget->resetButton, &QPushButton::clicked,
            this, &MainWindow::resetBounds);


    connect(mainWidget_->plannerWidget->geometricPlanning->timeLimit,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::setTimeLimit);
    connect(mainWidget_->plannerWidget->controlPlanning->timeLimit,
            QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &MainWindow::setTimeLimit);
}

MainWindow::~MainWindow() {}

void MainWindow::createActions() {
    openEnvironmentAct = new QAction("Open &Environment", this);
    openEnvironmentAct->setShortcut(QKeySequence::Open);
    connect(openEnvironmentAct, &QAction::triggered, this, &MainWindow::openEnvironment);

    openRobotAct = new QAction("Open &Robot", this);
    openRobotAct->setShortcut(QKeySequence::Open);
    connect(openRobotAct, &QAction::triggered, this, &MainWindow::openRobot);

    openConfigAct = new QAction("Open Problem &Configuration", this);
    openConfigAct->setShortcut(QKeySequence::Open);
    connect(openConfigAct, &QAction::triggered, this, &MainWindow::openConfig);

    saveConfigAct = new QAction("Save Problem Con&figuration", this);
    saveConfigAct->setShortcut(QKeySequence::Save);
    connect(saveConfigAct, &QAction::triggered, this, &MainWindow::saveConfig);

    openPathAct = new QAction("&Open Path", this);
    openPathAct->setShortcut(QKeySequence::Open);
    connect(openPathAct, &QAction::triggered, this, &MainWindow::openPath);

    savePathAct = new QAction("Save &Path", this);
    savePathAct->setShortcut(QKeySequence::Save);
    connect(savePathAct, &QAction::triggered, this, &MainWindow::savePath);

    savePlannerDataAct = new QAction("Save Roadmap/Tree", this);
    connect(savePlannerDataAct, &QAction::triggered, this, &MainWindow::savePlannerData);

    exitAct = new QAction("E&xit", this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &QMainWindow::close);

    logWindowAct = new QAction("Log Window", this);
    logWindowAct->setShortcut(QKeySequence("Ctrl+1"));
    connect(logWindowAct, &QAction::triggered, this, &MainWindow::showLogWindow);

    randMotionAct = new QAction("Random &Motion", this);
    randMotionAct->setShortcut(QKeySequence("Ctrl+M"));
    connect(randMotionAct, &QAction::triggered, this, &MainWindow::randMotion);

    commandWindowAct = new QAction("Command Window", this);
    commandWindowAct->setShortcut(QKeySequence("Ctrl+2"));
    connect(commandWindowAct, &QAction::triggered, this, &MainWindow::showCommandWindow);

    omplWebAct = new QAction("OMPL Web Site", this);
    connect(omplWebAct, &QAction::triggered, this, &MainWindow::omplWebSite);

    contactDevsAct = new QAction("Contact Developers", this);
    connect(contactDevsAct, &QAction::triggered, this, &MainWindow::contactDevs);

    emailListAct = new QAction("Email OMPL Mailing List", this);
    connect(emailListAct, &QAction::triggered, this, &MainWindow::emailList);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openEnvironmentAct);
    fileMenu->addAction(openRobotAct);
    fileMenu->addAction(openConfigAct);
    fileMenu->addAction(saveConfigAct);
    fileMenu->addAction(openPathAct);
    fileMenu->addAction(savePathAct);
    fileMenu->addAction(savePlannerDataAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    toolsMenu = menuBar()->addMenu("&Tools");
    toolsMenu->addAction(logWindowAct);
    toolsMenu->addAction(randMotionAct);
    toolsMenu->addAction(commandWindowAct);

    helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(omplWebAct);
    helpMenu->addAction(contactDevsAct);
    helpMenu->addAction(emailListAct);
}

void MainWindow::createRobotTypeList() {
    robotTypes = QList<QPair<QString, QString>> {
        {"SE3 Rigid Body", "SE3RigidBodyPlanning"},
        {"SE2 Rigid Body", "SE2RigidBodyPlanning"},
        {"Kinematic Car", "KinematicCarPlanning"},
        {"Dynamic Car", "DynamicCarPlanning"},
        {"Blimp", "BlimpPlanning"},
        {"Quadrotor", "QuadrotorPlanning"},
        {"Manipulator", "ManipulatorPlanning"}
    };

}

base::State* MainWindow::arrayToSE2State(const std::vector<double>& a) {
    auto* space = std::visit([](auto&& app) -> ompl::base::StateSpace* {
        return app->getGeometricComponentStateSpace().get();
    }, omplSetup_);
    
    auto* state = space->allocState();
    auto* se2 = state->as<base::SE2StateSpace::StateType>();
    se2->setX(a[0]);
    se2->setY(a[1]);
    se2->setYaw(a[2]);
    return state;
}

// Helper function to convert array to SE3 state
base::State* MainWindow::arrayToSE3State(const std::vector<double>& a) {
    auto* space = std::visit([](auto&& app) -> ompl::base::StateSpace* {
        return app->getGeometricComponentStateSpace().get();
    }, omplSetup_);
    
    auto* state = space->allocState();
    auto* se3 = state->as<base::SE3StateSpace::StateType>();
    se3->setX(a[0]);
    se3->setY(a[1]);
    se3->setZ(a[2]);
    
    const double norm = sqrt(a[3]*a[3] + a[4]*a[4] + a[5]*a[5] + a[6]*a[6]);
    se3->rotation().x = a[3]/norm;
    se3->rotation().y = a[4]/norm;
    se3->rotation().z = a[5]/norm;
    se3->rotation().w = a[6]/norm;
    
    return state;
}

void MainWindow::configureApp() {
    std::visit([&](auto&& app) {
      app->clear();
  
      // Retrieve the state array from the ProblemWidget.
      // (For a 3D pose box, the array is: [rotx, roty, rotz, posx, posy, posz])
      auto start = mainWidget_->problemWidget->getStartPose();
      auto goal  = mainWidget_->problemWidget->getGoalPose();
  
      base::ScopedState<> startState(app->getStateSpace());
      base::ScopedState<> goalState(app->getStateSpace());
  
      if (is3D) {
        auto *se3start = startState->as<base::SE3StateSpace::StateType>();
        se3start->setX(start[3]);
        se3start->setY(start[4]);
        se3start->setZ(start[5]);
        // Convert Euler angles (in degrees) to a quaternion.
        double rx = start[0] * M_PI/180.0;
        double ry = start[1] * M_PI/180.0;
        double rz = start[2] * M_PI/180.0;
        double cy = cos(rz * 0.5);
        double sy = sin(rz * 0.5);
        double cp = cos(ry * 0.5);
        double sp = sin(ry * 0.5);
        double cr = cos(rx * 0.5);
        double sr = sin(rx * 0.5);
        double qw = cr * cp * cy + sr * sp * sy;
        double qx = sr * cp * cy - cr * sp * sy;
        double qy = cr * sp * cy + sr * cp * sy;
        double qz = cr * cp * sy - sr * sp * cy;
        se3start->rotation().x = qx;
        se3start->rotation().y = qy;
        se3start->rotation().z = qz;
        se3start->rotation().w = qw;
  
        auto *se3goal = goalState->as<base::SE3StateSpace::StateType>();
        se3goal->setX(goal[3]);
        se3goal->setY(goal[4]);
        se3goal->setZ(goal[5]);
        double grx = goal[0] * M_PI/180.0;
        double gry = goal[1] * M_PI/180.0;
        double grz = goal[2] * M_PI/180.0;
        double gcy = cos(grz * 0.5);
        double gsy = sin(grz * 0.5);
        double gcp = cos(gry * 0.5);
        double gsp = sin(gry * 0.5);
        double gcr = cos(grx * 0.5);
        double gsr = sin(grx * 0.5);
        double gqw = gcr * gcp * gcy + gsr * gsp * gsy;
        double gqx = gsr * gcp * gcy - gcr * gsp * gsy;
        double gqy = gcr * gsp * gcy + gsr * gcp * gsy;
        double gqz = gcr * gcp * gsy - gsr * gsp * gcy;
        se3goal->rotation().x = gqx;
        se3goal->rotation().y = gqy;
        se3goal->rotation().z = gqz;
        se3goal->rotation().w = gqw;
      }
      else {
        auto *se2start = startState->as<base::SE2StateSpace::StateType>();
        se2start->setX(start[3]);
        se2start->setY(start[4]);
        se2start->setYaw(start[2] * M_PI/180.0);
        auto *se2goal = goalState->as<base::SE2StateSpace::StateType>();
        se2goal->setX(goal[3]);
        se2goal->setY(goal[4]);
        se2goal->setYaw(goal[2] * M_PI/180.0);
      }
  
      app->setStartAndGoalStates(startState, goalState);
  
      // Set bounds as before.
      auto low = mainWidget_->glViewer->getBoundsLow();
      auto high = mainWidget_->glViewer->getBoundsHigh();
      base::RealVectorBounds bounds(is3D ? 3 : 2);
      bounds.low[0] = low.x();
      bounds.low[1] = low.y();
      if (is3D)
        bounds.low[2] = low.z();
      bounds.high[0] = high.x();
      bounds.high[1] = high.y();
      if (is3D)
        bounds.high[2] = high.z();
  
      auto space = dynamic_cast<ompl::base::RealVectorStateSpace*>(
                     app->getGeometricComponentStateSpace().get());
      if (space)
        space->setBounds(bounds);
  
      app->setup();
    }, omplSetup_);
  }

void MainWindow::openEnvironment()
{
    // Show file dialog for environment mesh:
    QString fname = QFileDialog::getOpenFileName(
        this,
        "Open Environment",
        "",
        "Mesh Files (*.stl *.dae *.obj *.ply)"
    );

    if (!fname.isEmpty() && fname != environmentFile)
    {
        environmentFile = fname;

        // Set the environment mesh in whichever ompl::app instance
        std::visit([&](auto &appInstance)
        {
            // 1) Load geometry for collision checking
            appInstance->setEnvironmentMesh(environmentFile.toStdString());

            // 2) Create a RenderGeometry object. 
            //    Note: AppBase<T> inherits from RigidBodyGeometry, so we can pass it directly.
            ompl::app::RenderGeometry rg(
                *appInstance,                    // references RigidBodyGeometry
                appInstance->getGeometricStateExtractor()
            );

            // 3) Actually render environment. 
            //    This returns an int display list ID from omplapp’s assimp-based renderer.
            int envID = rg.renderEnvironment();

            // 4) Pass that int to your GLViewer. 
            //    E.g. you might store it to call glCallList(envID) in paintGL().
            mainWidget_->glViewer->setEnvironment(envID);

        }, omplSetup_);

        // Then do any bounding-box resets, etc.
        resetBounds();

        // If geometric & we have a robot, set collision-checking resolution
        if (isGeometric && !robotFile.isEmpty())
        {
            std::visit([&](auto &appInstance)
            {
                double resolution =
                    appInstance->getSpaceInformation()->getStateValidityCheckingResolution();
                mainWidget_->plannerWidget->geometricPlanning->resolution->setValue(resolution);
            }, omplSetup_);
        }
    }
}

void MainWindow::openRobot()
{
    // Show file dialog for robot mesh:
    QString fname = QFileDialog::getOpenFileName(
        this,
        "Open Robot",
        "",
        "Mesh Files (*.stl *.dae *.obj *.ply *.urdf)"
    );

    if (!fname.isEmpty() && fname != robotFile)
    {
        robotFile = fname;

        // Set the robot mesh in whichever ompl::app instance
        std::visit([&](auto &appInstance)
        {
            // 1) Load robot geometry
            appInstance->setRobotMesh(robotFile.toStdString());

            std::cout << "Loaded robot mesh: " << robotFile.toStdString() << std::endl;

            // 2) Create RenderGeometry object
            ompl::app::RenderGeometry rg(
                *appInstance,
                appInstance->getGeometricStateExtractor()
            );

            std::cout << "Rendered robot" << std::endl;

            // 3) Render robot and update viewer
            int robotID = rg.renderRobot();
            mainWidget_->glViewer->setRobot(robotID);

            std::cout << "Set robot in viewer" << std::endl;

            // 4) Infer environment bounds from robot
            appInstance->inferEnvironmentBounds();

            std::cout << "Inferred environment bounds" << std::endl;

            // Get default start state
            auto start = appInstance->getDefaultStartState();

            std::cout << "Got default start state" << std::endl;
            
            // Extract geometric component
            auto geometricStart = appInstance->getGeometricComponentState(start, 0);

            std::cout << "Extracted geometric component" << std::endl;

            // Convert OMPL state to pose representation
            std::array<double, 6> pose;
            std::vector<double> pose_vec(6);
            appInstance->getStateSpace()->copyToReals(pose_vec, geometricStart.get());
            std::copy_n(pose_vec.begin(), 6, pose.begin());

            // Update UI elements
            mainWidget_->problemWidget->setStartPose(pose, is3D);
            mainWidget_->problemWidget->setGoalPose(pose, is3D);

            // Set collision checking resolution if geometric
            if (isGeometric) {
                double resolution = appInstance->getSpaceInformation()
                    ->getStateValidityCheckingResolution();
                mainWidget_->plannerWidget->geometricPlanning->resolution->setValue(resolution);
            }

            // Update bounds in viewer
            auto space = dynamic_cast<ompl::base::RealVectorStateSpace*>(appInstance->getGeometricComponentStateSpace().get());
            base::RealVectorBounds bounds(is3D ? 3 : 2);
            if (space) {
                bounds = space->getBounds();
            }
            QVector3D low(bounds.low[0], bounds.low[1], bounds.low[2]);
            QVector3D high(bounds.high[0], bounds.high[1], bounds.high[2]);
            mainWidget_->glViewer->setBounds(low, high);

        }, omplSetup_);
    }
}

void MainWindow::openConfig() {
    QString fileName = QFileDialog::getOpenFileName(this, 
        "Open Problem Configuration", "", "Config Files (*.cfg)");
    
    if (!fileName.isEmpty()) {
        QSettings config(fileName, QSettings::IniFormat);
        
        // Determine robot type
        if (config.contains("problem/start.z")) {
            QString ctype = config.value("problem/control", "").toString();
            QString className;
            if (ctype == "blimp") className = "BlimpPlanning";
            else if (ctype == "quadrotor") className = "QuadrotorPlanning";
            else className = "SE3RigidBodyPlanning";
            
            auto it = std::find_if(robotTypes.begin(), robotTypes.end(),
                [&](const QPair<QString, QString>& p) { return p.second == className; });
            
            if (it != robotTypes.end()) {
                mainWidget_->problemWidget->robotTypeSelect->setCurrentIndex(it - robotTypes.begin());
            }
        } else {
            QString ctype = config.value("problem/control", "").toString();
            QString className;
            if (ctype == "kinematic_car") className = "KinematicCarPlanning";
            else if (ctype == "dynamic_car") className = "DynamicCarPlanning";
            else className = "SE2RigidBodyPlanning";
            
            auto it = std::find_if(robotTypes.begin(), robotTypes.end(),
                [&](const QPair<QString, QString>& p) { return p.second == className; });
            
            if (it != robotTypes.end()) {
                mainWidget_->problemWidget->robotTypeSelect->setCurrentIndex(it - robotTypes.begin());
            }
        }

        // Load environment and robot
        QString cfgDir = QFileInfo(fileName).absolutePath();
        environmentFile = cfgDir + "/" + config.value("problem/world").toString();
        robotFile = cfgDir + "/" + config.value("problem/robot").toString();
        
        std::visit([&](auto&& app) {
            app->setEnvironmentMesh(environmentFile.toStdString());
            app->setRobotMesh(robotFile.toStdString());
            
            // Render and set in viewer
            ompl::app::RenderGeometry rg(*app, app->getGeometricStateExtractor());
            mainWidget_->glViewer->setEnvironment(rg.renderEnvironment());
            mainWidget_->glViewer->setRobot(rg.renderRobot());
        }, omplSetup_);
        
        resetBounds();

        // Load start/goal states
        base::State* start = nullptr;
        base::State* goal = nullptr;
        
        if (is3D) {
            start = arrayToSE3State({
                config.value("problem/start.x").toDouble(),
                config.value("problem/start.y").toDouble(),
                config.value("problem/start.z").toDouble(),
                config.value("problem/start.axis.x").toDouble(),
                config.value("problem/start.axis.y").toDouble(),
                config.value("problem/start.axis.z").toDouble(),
                config.value("problem/start.theta").toDouble()
            });
            
            goal = arrayToSE3State({
                config.value("problem/goal.x").toDouble(),
                config.value("problem/goal.y").toDouble(),
                config.value("problem/goal.z").toDouble(),
                config.value("problem/goal.axis.x").toDouble(),
                config.value("problem/goal.axis.y").toDouble(),
                config.value("problem/goal.axis.z").toDouble(),
                config.value("problem/goal.theta").toDouble()
            });
        } else {
            start = arrayToSE2State({
                config.value("problem/start.x").toDouble(),
                config.value("problem/start.y").toDouble(),
                config.value("problem/start.theta").toDouble()
            });
            
            goal = arrayToSE2State({
                config.value("problem/goal.x").toDouble(),
                config.value("problem/goal.y").toDouble(),
                config.value("problem/goal.theta").toDouble()
            });
        }

        // Convert to pose arrays for UI
        std::array<double, 6> startPose{}, goalPose{};
        std::visit([&](auto&& app) {
            std::vector<double> reals;
            app->getStateSpace()->copyToReals(reals, start);
            std::copy_n(reals.begin(), 6, startPose.begin());
            reals.clear();
            app->getStateSpace()->copyToReals(reals, goal);
            std::copy_n(reals.begin(), 6, goalPose.begin());
        }, omplSetup_);

        mainWidget_->problemWidget->setStartPose(startPose, is3D);
        mainWidget_->problemWidget->setGoalPose(goalPose, is3D);

        // Cleanup
        std::visit([&](auto&& app) { 
            app->getStateSpace()->freeState(start);
            app->getStateSpace()->freeState(goal);
        }, omplSetup_);

        // Load bounds
        if (is3D && config.contains("problem/volume.min.x")) {
            base::RealVectorBounds bounds(3);
            bounds.low[0] = config.value("problem/volume.min.x").toDouble();
            bounds.low[1] = config.value("problem/volume.min.y").toDouble();
            bounds.low[2] = config.value("problem/volume.min.z").toDouble();
            bounds.high[0] = config.value("problem/volume.max.x").toDouble();
            bounds.high[1] = config.value("problem/volume.max.y").toDouble();
            bounds.high[2] = config.value("problem/volume.max.z").toDouble();
            
            std::visit([&](auto&& app) {
                auto space = dynamic_cast<ompl::base::RealVectorStateSpace*>(app->getGeometricComponentStateSpace().get());
                if (space) {
                    space->setBounds(bounds);
                }
            }, omplSetup_);
            
            mainWidget_->glViewer->setBounds(
                QVector3D(bounds.low[0], bounds.low[1], bounds.low[2]),
                QVector3D(bounds.high[0], bounds.high[1], bounds.high[2])
            );
        }
        else if (!is3D && config.contains("problem/volume.min.x")) {
            base::RealVectorBounds bounds(2);
            bounds.low[0] = config.value("problem/volume.min.x").toDouble();
            bounds.low[1] = config.value("problem/volume.min.y").toDouble();
            bounds.high[0] = config.value("problem/volume.max.x").toDouble();
            bounds.high[1] = config.value("problem/volume.max.y").toDouble();
            
            std::visit([&](auto&& app) {
                auto space = dynamic_cast<ompl::base::RealVectorStateSpace*>(app->getGeometricComponentStateSpace().get());
                if (space) {
                    space->setBounds(bounds);
                }
            }, omplSetup_);
            
            mainWidget_->glViewer->setBounds(
                QVector3D(bounds.low[0], bounds.low[1], 0),
                QVector3D(bounds.high[0], bounds.high[1], 0)
            );
        }
    }
}

void MainWindow::saveConfig() {
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Save Problem Configuration", "config.cfg", "Config Files (*.cfg)");
    
    if (!fileName.isEmpty()) {
        QSettings config(fileName, QSettings::IniFormat);
        
        // Basic info
        config.setValue("problem/robot", robotFile);
        config.setValue("problem/world", environmentFile);
        
        // Start and goal poses
        auto startPose = mainWidget_->problemWidget->getStartPose();
        auto goalPose = mainWidget_->problemWidget->getGoalPose();
        
        if (is3D) {
            config.setValue("problem/start.x", startPose[0]);
            config.setValue("problem/start.y", startPose[1]);
            config.setValue("problem/start.z", startPose[2]);
            // Rotation handling needed
            // Similar for goal pose
        } else {
            config.setValue("problem/start.x", startPose[0]);
            config.setValue("problem/start.y", startPose[1]);
            config.setValue("problem/start.theta", startPose[5]); // Assuming yaw
            config.setValue("problem/goal.x", goalPose[0]);
            config.setValue("problem/goal.y", goalPose[1]);
            config.setValue("problem/goal.theta", goalPose[5]);
        }
        
        // Bounds
        auto bounds = mainWidget_->glViewer->getBoundsLow();
        if (is3D) {
            config.setValue("problem/volume.min.x", bounds.x());
            config.setValue("problem/volume.min.y", bounds.y());
            config.setValue("problem/volume.min.z", bounds.z());
            auto high = mainWidget_->glViewer->getBoundsHigh();
            config.setValue("problem/volume.max.x", high.x());
            config.setValue("problem/volume.max.y", high.y());
            config.setValue("problem/volume.max.z", high.z());
        } else {
            config.setValue("problem/volume.min.x", bounds.x());
            config.setValue("problem/volume.min.y", bounds.y());
            auto high = mainWidget_->glViewer->getBoundsHigh();
            config.setValue("problem/volume.max.x", high.x());
            config.setValue("problem/volume.max.y", high.y());
        }
        
        // Planner objectives
        config.setValue("problem/objective", 
            mainWidget_->problemWidget->objectiveSelect->currentText().replace(" ", "_"));
        config.setValue("problem/objective.threshold", 
            mainWidget_->problemWidget->objectiveThreshold->value());
    }
}

void MainWindow::openPath() {
    QString fileName = QFileDialog::getOpenFileName(this, 
        "Open Path", "", "Text Files (*.txt)");
    
    if (!fileName.isEmpty()) {
        std::ifstream file(fileName.toStdString());
        std::string line;
        std::vector<base::State*> path;
        
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<double> values;
            double value;
            
            while (iss >> value) {
                values.push_back(value);
            }
            
            if (values.size() >= 7) {
                path.push_back(arrayToSE3State(values));
            } else if (values.size() >= 3) {
                path.push_back(arrayToSE2State(values));
            } else {
                OMPL_ERROR("Invalid path format");
                return;
            }
        }
        
        // Update solution path
        solutionPath_ = path;
        geometric::PathGeometric pathGeometric(
            std::visit([](auto&& app) -> base::SpaceInformationPtr {
                return app->getSpaceInformation();
            }, omplSetup_)
        );
        
        for (auto* state : path) {
            pathGeometric.append(state);
        }
        
        setSolutionPath(pathGeometric);
    }
}

void MainWindow::savePath() {
    if (solutionPath_.empty()) return;
    
    QString fileName = QFileDialog::getSaveFileName(this, 
        "Save Path", "path.txt", "Text Files (*.txt)");
    
    if (!fileName.isEmpty()) {
        std::ofstream file(fileName.toStdString());
        
        for (auto* state : solutionPath_) {
            std::vector<double> reals;
            std::visit([&](auto&& app) {
                app->getStateSpace()->copyToReals(reals, state);
            }, omplSetup_);
            
            for (double val : reals) {
                file << val << " ";
            }
            file << "\n";
        }
    }
}

void MainWindow::savePlannerData() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Roadmap/Tree", "plannerData.graphml", "GraphML Files (*.graphml)");
    if (!fileName.isEmpty()) {
        // Save planner data logic here
    }
}

void MainWindow::setRobotType(int value)
{
    // 1) Clear environmentFile, robotFile, etc.
    environmentFile.clear();
    robotFile.clear();
    solutionPath_.clear();     // or call clear(true) if you want to reset the viewer, etc.
    clear(true);

    // 2) Retrieve the selected robot type from our QList<QPair<QString,QString>>
    if (value < 0 || value >= robotTypes.size()) return;
    auto selected = robotTypes[value];
    QString displayName = selected.first;   // e.g. "SE3 Rigid Body"
    QString className   = selected.second;  // e.g. "SE3RigidBodyPlanning"

    // 3) Instantiate the correct OMPL app based on className
    //    and store in our std::variant (omplSetup_).
    if (className == "SE3RigidBodyPlanning")
    {
        auto se3 = std::make_shared<ompl::app::SE3RigidBodyPlanning>();
        omplSetup_ = se3;  // variant now holds AppBase<GEOMETRIC>
        isGeometric = true;
        is3D        = true;
    }
    else if (className == "SE2RigidBodyPlanning")
    {
        auto se2 = std::make_shared<ompl::app::SE2RigidBodyPlanning>();
        omplSetup_ = se2;
        isGeometric = true;
        is3D        = false;
    }
    else if (className == "KinematicCarPlanning")
    {
        auto kinCar = std::make_shared<ompl::app::KinematicCarPlanning>();
        omplSetup_  = kinCar;  // variant holds AppBase<CONTROL>
        isGeometric = false;
        is3D        = false;
    }
    else if (className == "DynamicCarPlanning")
    {
        auto dynCar = std::make_shared<ompl::app::DynamicCarPlanning>();
        omplSetup_  = dynCar;
        isGeometric = false;
        is3D        = false;
    }
    else if (className == "BlimpPlanning")
    {
        auto blimp = std::make_shared<ompl::app::BlimpPlanning>();
        omplSetup_ = blimp;
        isGeometric = false;
        is3D        = true;
    }
    else if (className == "QuadrotorPlanning")
    {
        auto quad = std::make_shared<ompl::app::QuadrotorPlanning>();
        omplSetup_ = quad;
        isGeometric = false;
        is3D        = true;
    }
    else if (className == "ManipulatorPlanning")
    {
        auto manipulator = std::make_shared<ompl::app::ManipulatorPlanning>();
        omplSetup_ = manipulator;
        isGeometric = true;
        is3D        = true;
    }
    else
    {
        // Optionally handle unknown className
        qWarning() << "Unknown className:" << className;
        return;
    }

    // 4) Update your UI (which tab or stacked widget to display, etc.)
    //    PlannerWidget: 0 => geometric, 1 => control
    mainWidget_->plannerWidget->setCurrentIndex(isGeometric ? 0 : 1);
    //    ProblemWidget: 0 => 3D, 1 => 2D
    mainWidget_->problemWidget->poses->setCurrentIndex(is3D ? 0 : 1);

    if (isGeometric)
    {
        mainWidget_->plannerWidget->geometricPlanning->populatePlannerList(true);
    }
    else
    {
        mainWidget_->plannerWidget->controlPlanning->populatePlannerList(false);
    }
}

void MainWindow::setTimeLimit(double value) {
    timeLimitValue = value;
}

void MainWindow::solve() {
    configureApp();
    
    // Create the planner based on the user's selection.
    std::visit([&](auto&& app) {
        ob::PlannerPtr planner = createPlanner();
        if (planner)
            app->setPlanner(planner);
        else
            qDebug() << "No valid planner created.";
    }, omplSetup_);

    base::PlannerStatus solved;
    std::visit([&](auto&& app) {
        solved = app->solve(timeLimitValue);
    }, omplSetup_);
    
    updateSolutionStatus(solved.asString());
    
    if (solved) {
        std::visit([&](auto&& app) {
            std::cout << "Found solution" << std::endl;
            std::cout << "Solution path length: " << app->getProblemDefinition()->getSolutionPath()->length() << std::endl;
            auto path = app->getSolutionPath();
            path.interpolate();
            setSolutionPath(path);
            std::cout << "Solution path set." << std::endl;
        }, omplSetup_);
        
        // Also, get and display planner data:
        ob::PlannerData pd(std::visit([](auto&& app) -> ob::SpaceInformationPtr {
            return app->getSpaceInformation();
        }, omplSetup_));
        std::visit([&](auto&& app) {
            app->getPlannerData(pd);
        }, omplSetup_);
        mainWidget_->glViewer->setPlannerDataListFromPlannerData(pd);
    }
}

ob::PlannerPtr MainWindow::createPlanner() {
    // Get the space information from the current app:
    ob::SpaceInformationPtr si = std::visit([](auto&& app) -> ob::SpaceInformationPtr {
        return app->getSpaceInformation();
    }, omplSetup_);

    ob::PlannerPtr planner;
    if (isGeometric) {
        // Get the current selection from the geometric planner widget.
        int idx = mainWidget_->plannerWidget->geometricPlanning->plannerSelect->currentIndex();
        if (idx < 0 || idx >= mainWidget_->plannerWidget->geometricPlanning->plannerList.size()) {
            qDebug() << "Invalid planner index for geometric planning.";
            return nullptr;
        }
        QString plannerId = mainWidget_->plannerWidget->geometricPlanning->plannerList[idx].plannerId;
        // Look up in the geometric registry:
        auto &reg = ompl::geometric::PlannerRegistry::getInstance();
        auto it = reg.getPlanners().find(plannerId.toStdString());
        if (it != reg.getPlanners().end()) {
            planner = it->second(si);
        } else {
            qDebug() << "Geometric planner" << plannerId << "not found in registry.";
        }
    } else {
        // Get the current selection from the control planner widget.
        int idx = mainWidget_->plannerWidget->controlPlanning->plannerSelect->currentIndex();
        if (idx < 0 || idx >= mainWidget_->plannerWidget->controlPlanning->plannerList.size()) {
            qDebug() << "Invalid planner index for control planning.";
            return nullptr;
        }
        QString plannerId = mainWidget_->plannerWidget->controlPlanning->plannerList[idx].plannerId;
        // Look up in the control registry:
        auto &reg = ompl::control::PlannerRegistry::getInstance();
        auto it = reg.getPlanners().find(plannerId.toStdString());
        if (it != reg.getPlanners().end()) {
            // For control planners, cast space information appropriately.
            auto ctrlSI = std::static_pointer_cast<ompl::control::SpaceInformation>(si);
            planner = it->second(ctrlSI);
        } else {
            qDebug() << "Control planner" << plannerId << "not found in registry.";
        }
    }
    return planner;
}

void MainWindow::setSolutionPath(const ompl::control::PathControl &path)
{
    solutionPath_.clear();
    
    // Get the state space from the current OMPL app.
    auto space = std::visit([](auto&& app) -> ompl::base::StateSpace* {
        return app->getStateSpace().get();
    }, omplSetup_);
    
    // Copy states from the control path.
    for (size_t i = 0; i < path.getStateCount(); ++i) {
        auto* stateCopy = space->allocState();
        space->copyState(stateCopy, path.getState(i));
        solutionPath_.push_back(stateCopy);
    }
    
    // Convert the solution path to the format needed by GLViewer.
    QVector<QVector<float>> glPath;
    std::visit([&](auto&& app) {
        for (auto* state : solutionPath_) {
            std::vector<double> reals;
            app->getStateSpace()->copyToReals(reals, state);
            QVector<float> vec;
            for (double val : reals)
                vec << static_cast<float>(val);
            glPath.append(vec);
        }
    }, omplSetup_);
    
    // Pass the converted path to the viewer.
    mainWidget_->glViewer->setSolutionPath(glPath);
}

void MainWindow::setSolutionPath(const geometric::PathGeometric& path) {
    solutionPath_.clear();
    
    auto space = std::visit([](auto&& app) -> ompl::base::StateSpace* {
        return app->getStateSpace().get();
    }, omplSetup_);

    for (size_t i = 0; i < path.getStateCount(); ++i) {
        auto* stateCopy = space->allocState();
        space->copyState(stateCopy, path.getState(i));
        solutionPath_.push_back(stateCopy);
    }
    
    // Convert path to GLViewer format
    QVector<QVector<float>> glPath;
    std::visit([&](auto&& app) {
        for (auto* state : solutionPath_) {
            std::vector<double> reals;
            app->getStateSpace()->copyToReals(reals, state);
            QVector<float> vec;
            for (double val : reals) vec << static_cast<float>(val);
            glPath.append(vec);
        }
    }, omplSetup_);
    
    mainWidget_->glViewer->setSolutionPath(glPath);
}

void MainWindow::updateSolutionStatus(const std::string& status) {
    if (status == "Exact solution") {
        mainWidget_->solveWidget->solvedLabel->setText("Found solution");
    } else if (status == "Approximate solution") {
        mainWidget_->solveWidget->solvedLabel->setText("Approximate solution");
    } else {
        mainWidget_->solveWidget->solvedLabel->setText("No solution found");
    }
}

void MainWindow::clear(bool deepClean) {
    mainWidget_->solveWidget->solvedLabel->clear();
    mainWidget_->glViewer->clear(deepClean);
}

void MainWindow::resetBounds() {
    // Reset bounds logic here
}

void MainWindow::showLogWindow() {
    // Show log window logic here
}

void MainWindow::showCommandWindow() {
    // Show command window logic here
}

void MainWindow::omplWebSite() {
    QDesktopServices::openUrl(QUrl("http://ompl.kavrakilab.org"));
}

void MainWindow::contactDevs() {
    QDesktopServices::openUrl(QUrl("mailto:ompl-devel@lists.sourceforge.net"));
}

void MainWindow::emailList() {
    QDesktopServices::openUrl(QUrl("mailto:ompl-users@lists.sourceforge.net"));
}

void MainWindow::randMotion() {
    // Random motion logic here
}
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <pinocchio/fwd.hpp>

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>
#include <QTabWidget>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QSlider>
#include <QStackedWidget>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QDesktopServices>
#include <QUrl>
#include <QSettings>

#include "GLViewer.h"
#include "MainWidget.h"

#include <memory>
#include <variant>
#include <vector>
#include <array>
#include <omplapp/apps/SE3RigidBodyPlanning.h>
#include <omplapp/apps/SE2RigidBodyPlanning.h>
#include <omplapp/apps/KinematicCarPlanning.h>
#include <omplapp/apps/DynamicCarPlanning.h>
#include <omplapp/apps/BlimpPlanning.h>
#include <omplapp/apps/QuadrotorPlanning.h>
#include <omplapp/apps/ManipulatorPlanning.h>
#include <omplapp/apps/AppBase.h>
#include <ompl/base/Planner.h>
#include <ompl/base/SpaceInformation.h>

#include <omplapp/graphics/RenderGeometry.h>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openEnvironment();
    void openRobot();
    void openConfig();
    void saveConfig();
    void openPath();
    void savePath();
    void savePlannerData();
    void setRobotType(int value);
    void setTimeLimit(double value);
    void solve();
    void clear(bool deepClean = false);
    void resetBounds();
    void showLogWindow();
    void showCommandWindow();
    void omplWebSite();
    void contactDevs();
    void emailList();
    void randMotion();

    void setSolutionPath(const ompl::geometric::PathGeometric& path);
    void setSolutionPath(const ompl::control::PathControl& path);
    void updateSolutionStatus(const std::string& status);
    ompl::base::State* arrayToSE2State(const std::vector<double>& a);
    ompl::base::State* arrayToSE3State(const std::vector<double>& a);


private:
    void createActions();
    void createMenus();
    void createRobotTypeList();
    void configureApp();
    ob::PlannerPtr createPlanner();

    QAction *openEnvironmentAct;
    QAction *openRobotAct;
    QAction *openConfigAct;
    QAction *saveConfigAct;
    QAction *openPathAct;
    QAction *savePathAct;
    QAction *savePlannerDataAct;
    QAction *exitAct;
    QAction *logWindowAct;
    QAction *randMotionAct;
    QAction *commandWindowAct;
    QAction *omplWebAct;
    QAction *contactDevsAct;
    QAction *emailListAct;

    QMenu *fileMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;

    QTextEdit *logView;
    QTabWidget *tabWidget;
    QComboBox *robotTypeSelect;
    QDoubleSpinBox *timeLimit;
    QPushButton *solveButton;
    QPushButton *clearButton;
    QSlider *speedSlider;
    QStackedWidget *plannerWidget;
    QGridLayout *layout;
    QGroupBox *boundsWidget;
    QLabel *solvedLabel;

    GLViewer *glViewer;
    QTimer *timer;
    double timeLimitValue;
    bool isGeometric;
    bool is3D;
    QString environmentFile;
    QString robotFile;

    MainWidget *mainWidget_;

    QList<QPair<QString, QString>> robotTypes;

    std::variant<
    std::shared_ptr<ompl::app::AppBase<ompl::app::AppType::GEOMETRIC>>,
    std::shared_ptr<ompl::app::AppBase<ompl::app::AppType::CONTROL>> 
    > omplSetup_;

    std::shared_ptr<ompl::base::Planner> planner_;
    ompl::base::PlannerSolution solution_;
    std::vector<ompl::base::State*> solutionPath_;

};

#endif // MAINWINDOW_H
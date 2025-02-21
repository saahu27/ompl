// MainWidget.cpp
#include "MainWidget.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTabWidget>

MainWidget::MainWidget(const QList<QPair<QString, QString>> &robotTypes, QWidget *parent)
    : QWidget(parent)
{
    // Create sub-widgets
    glViewer = new GLViewer(this);
    glViewer->setMinimumSize(400, 300);
    glViewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // Allow expansion
    
    problemWidget = new ProblemWidget(robotTypes, this);
    plannerWidget = new PlannerWidget(this);
    boundsWidget = new BoundsWidget(this);
    solveWidget = new SolveWidget(this);

    // Create a tab widget to hold problemWidget, plannerWidget, boundsWidget
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->addTab(problemWidget, tr("Problem"));
    tabWidget->addTab(plannerWidget, tr("Planner"));
    tabWidget->addTab(boundsWidget, tr("Bounding box"));

    // A layout for the entire widget
    QGridLayout *layout = new QGridLayout(this);
    // Place glViewer in the left side spanning 2 rows
    layout->addWidget(glViewer, 0, 0, 2, 1);
    // Place tabWidget in row 0, col 1
    layout->addWidget(tabWidget, 0, 1);
    // Place solveWidget in row 1, col 1
    layout->addWidget(solveWidget, 1, 1);

    setLayout(layout);

    // Example: Connect signals from problemWidget to glViewer if needed
    connect(problemWidget, &ProblemWidget::startChanged, glViewer, &GLViewer::setStartPose);
    connect(problemWidget, &ProblemWidget::goalChanged, glViewer, &GLViewer::setGoalPose);

    // Connect solveWidget signals to glViewer if needed (like in python code)
    connect(solveWidget->explorationVizSelect, QOverload<int>::of(&QComboBox::currentIndexChanged),
            glViewer, &GLViewer::showPlannerData);
    connect(solveWidget->animateCheck, &QCheckBox::toggled,
            glViewer, &GLViewer::toggleAnimation);
    connect(solveWidget->speedSlider, &QSlider::valueChanged,
            glViewer, &GLViewer::setSpeed);
}

#include "ProblemWidget.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include "Pose3DBox.h"
#include "Pose2DBox.h"

ProblemWidget::ProblemWidget(const QList<QPair<QString, QString>> &robotTypes,
                             QWidget *parent)
    : QWidget(parent)
{
    QLabel *robotTypeLabel = new QLabel(tr("Robot type"), this);
    robotTypeSelect = new QComboBox(this);
    for (auto &rt : robotTypes) {
        // rt.first = internalName, rt.second = user-friendly
        robotTypeSelect->addItem(rt.second);
    }
    robotTypeSelect->setMaximumSize(200, 9999);

    startPose3D = new Pose3DBox(tr("Start pose"), this);
    goalPose3D = new Pose3DBox(tr("Goal pose"), this);
    startPose2D = new Pose2DBox(tr("Start pose"), this);
    goalPose2D = new Pose2DBox(tr("Goal pose"), this);

    QWidget *startGoal3D = new QWidget(this);
    QVBoxLayout *layout3D = new QVBoxLayout(startGoal3D);
    layout3D->addWidget(startPose3D);
    layout3D->addWidget(goalPose3D);
    startGoal3D->setLayout(layout3D);

    QWidget *startGoal2D = new QWidget(this);
    QGridLayout *layout2D = new QGridLayout(startGoal2D);
    layout2D->addWidget(startPose2D, 0, 0, 1, 2);
    layout2D->addWidget(goalPose2D, 1, 0, 1, 2);
    startGoal2D->setLayout(layout2D);

    poses = new QStackedWidget(this);
    poses->addWidget(startGoal3D); // index 0 => 3D
    poses->addWidget(startGoal2D); // index 1 => 2D

    // objective combo
    objectiveSelect = new QComboBox(this);
    // e.g. "length", "max min clearance", "mechanical work"
    objectiveSelect->addItem("length");
    objectiveSelect->addItem("max min clearance");
    objectiveSelect->addItem("mechanical work");

    objectiveThreshold = new QDoubleSpinBox(this);
    objectiveThreshold->setRange(0, 10000);
    objectiveThreshold->setSingleStep(1);
    objectiveThreshold->setValue(10000);

    // Layout for the widget
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(robotTypeLabel, 0, 0);
    layout->addWidget(robotTypeSelect, 0, 1);
    layout->addWidget(poses, 1, 0, 1, 2);
    layout->addWidget(new QLabel("Opt. objective"), 2, 0);
    layout->addWidget(objectiveSelect, 2, 1);
    layout->addWidget(new QLabel("Cost threshold"), 3, 0);
    layout->addWidget(objectiveThreshold, 3, 1);
    setLayout(layout);

    // Connect signals from the 3D/2D pose boxes to ProblemWidget
    connect(startPose3D, &Pose3DBox::valueChanged,
            this, &ProblemWidget::startPoseChange);
    connect(goalPose3D, &Pose3DBox::valueChanged,
            this, &ProblemWidget::goalPoseChange);
    connect(startPose2D, &Pose2DBox::valueChanged,
            this, &ProblemWidget::startPoseChange);
    connect(goalPose2D, &Pose2DBox::valueChanged,
            this, &ProblemWidget::goalPoseChange);
}

std::array<double,6> ProblemWidget::getStartPose() const
{
    if (poses->currentIndex() == 0)
        return startPose3D->getPose();  // returns array
    else
        return startPose2D->getPose();
}

std::array<double,6> ProblemWidget::getGoalPose() const
{
    if (poses->currentIndex() == 0)
        return goalPose3D->getPose();
    else
        return goalPose2D->getPose();
}

void ProblemWidget::setStartPose(const std::array<double,6> &pose, bool is3D)
{
    if (is3D)
        startPose3D->setPose(pose);
    else
        startPose2D->setPose(pose);
    // Possibly update the QStackedWidget index (0=3D,1=2D) if needed
}

void ProblemWidget::setGoalPose(const std::array<double,6> &pose, bool is3D)
{
    if (is3D)
        goalPose3D->setPose(pose);
    else
        goalPose2D->setPose(pose);
}

void ProblemWidget::startPoseChange(const std::array<double,6> &value)
{
    emit startChanged(value);
}

void ProblemWidget::goalPoseChange(const std::array<double,6> &value)
{
    emit goalChanged(value);
}

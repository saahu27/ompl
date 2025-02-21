// ProblemWidget.h
#ifndef PROBLEMWIDGET_H
#define PROBLEMWIDGET_H
#include <pinocchio/fwd.hpp>
#include <QWidget>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QStackedWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSignalMapper>
#include "Pose3DBox.h"
#include "Pose2DBox.h"

class ProblemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProblemWidget(const QList<QPair<QString, QString>> &robotTypes,
                           QWidget *parent = nullptr);

    // For reading which robot type is chosen
    QComboBox *robotTypeSelect;
    // The stacked widget that has 3D or 2D
    QStackedWidget *poses;
    Pose3DBox *startPose3D;
    Pose3DBox *goalPose3D;
    Pose2DBox *startPose2D;
    Pose2DBox *goalPose2D;

    // e.g. objective selection
    QComboBox *objectiveSelect;
    QDoubleSpinBox *objectiveThreshold;

    // Access to start/goal poses
    // This replicates python's getStartPose() / getGoalPose()
    // In real usage, you'd return e.g. an ompl::base::State*
    // or your own struct. We'll do a placeholder here.
    // The python code uses ob.State() calls. We can mimic with a small struct.
    // Or store angles in an array. Up to you.
    // For demonstration:
    std::array<double,6> getStartPose() const;
    std::array<double,6> getGoalPose() const;

public slots:
    void setStartPose(/* maybe your type? or array? */ const std::array<double,6> &pose, bool is3D);
    void setGoalPose(const std::array<double,6> &pose, bool is3D);

signals:
    void startChanged(const std::array<double,6> &pose);
    void goalChanged(const std::array<double,6> &pose);

private slots:
    void startPoseChange(const std::array<double,6> &value);
    void goalPoseChange(const std::array<double,6> &value);

private:
    // Possibly an elevation2D QDoubleSpinBox if you want that
};

#endif // PROBLEMWIDGET_H

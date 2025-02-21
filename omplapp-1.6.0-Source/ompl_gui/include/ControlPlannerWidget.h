#ifndef CONTROLPLANNERWIDGET_H
#define CONTROLPLANNERWIDGET_H

#include "PlannerHelperWidget.h"
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QLabel>

/**
 * @brief ControlPlannerWidget corresponds to the "Planning with controls" tab
 *        in the original Python code. It has spinboxes for time limit, propagation step,
 *        min/max control duration, and a goal distance threshold.
 */
class ControlPlannerWidget : public PlannerHelperWidget
{
    Q_OBJECT
public:
    explicit ControlPlannerWidget(QWidget *parent = nullptr);

    QDoubleSpinBox *timeLimit;           // The time limit for planning (seconds)
    QDoubleSpinBox *propagation;         // Propagation step size
    QSpinBox       *minControlDuration;  // Min # of control steps
    QSpinBox       *maxControlDuration;  // Max # of control steps
    QDoubleSpinBox *threshold;           // Goal distance threshold
};

#endif // CONTROLPLANNERWIDGET_H

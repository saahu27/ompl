#include <pinocchio/fwd.hpp>
#include "ControlPlannerWidget.h"
#include <QGridLayout>
#include <QLabel>

ControlPlannerWidget::ControlPlannerWidget(QWidget *parent)
    : PlannerHelperWidget("Planning with controls", parent)
{
    // A label & spinbox for time limit
    QLabel *timeLabel = new QLabel(tr("Time (sec.)"), this);
    timeLimit = new QDoubleSpinBox(this);
    timeLimit->setRange(0, 10000);
    timeLimit->setSingleStep(1);
    timeLimit->setValue(10.0);

    // A label & spinbox for propagation step size
    QLabel *propagationLabel = new QLabel(tr("Propagation step size"), this);
    propagationLabel->setAlignment(Qt::AlignRight);
    propagation = new QDoubleSpinBox(this);
    propagation->setRange(0.01, 1000.00);
    propagation->setSingleStep(0.01);
    propagation->setValue(0.2);
    propagation->setDecimals(2);

    // A label & spinboxes for control duration (min/max # steps)
    QLabel *durationLabel = new QLabel(tr("Control duration (min/max #steps)"), this);
    durationLabel->setAlignment(Qt::AlignRight);
    minControlDuration = new QSpinBox(this);
    minControlDuration->setRange(1, 1000);
    minControlDuration->setValue(1);

    maxControlDuration = new QSpinBox(this);
    maxControlDuration->setRange(1, 1000);
    maxControlDuration->setValue(20);

    // A label & spinbox for goal distance threshold
    QLabel *thresholdLabel = new QLabel(tr("Goal distance threshold"), this);
    thresholdLabel->setAlignment(Qt::AlignRight);
    threshold = new QDoubleSpinBox(this);
    threshold->setRange(0.0, 100.00);
    threshold->setSingleStep(0.01);
    threshold->setValue(1.0);
    threshold->setDecimals(2);

    // Now place them in this group's layout (inherited from PlannerHelperWidget).
    // By default, PlannerHelperWidget uses a QGridLayout that has "Planner" label,
    // the plannerSelect combobox, and the stackedWidget in rows 0..1. 
    // So we’ll place our spinboxes below them.

    QGridLayout *lay = qobject_cast<QGridLayout*>(layout());
    if (!lay) return;

    // Place time limit row
    int row = lay->rowCount();
    lay->addWidget(timeLabel, row, 0, Qt::AlignRight);
    lay->addWidget(timeLimit, row, 1);
    row++;

    // Place propagation row
    lay->addWidget(propagationLabel, row, 0, Qt::AlignRight);
    lay->addWidget(propagation, row, 1);
    row++;

    // Place control duration row
    lay->addWidget(durationLabel, row, 0);
    // We can put min & max side by side if we want
    lay->addWidget(minControlDuration, row, 1);
    row++;
    lay->addWidget(maxControlDuration, row, 1);
    row++;

    // Place threshold row
    lay->addWidget(thresholdLabel, row, 0, Qt::AlignRight);
    lay->addWidget(threshold, row, 1);
}

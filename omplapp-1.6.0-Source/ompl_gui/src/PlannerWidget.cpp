// PlannerWidget.cpp
#include "PlannerWidget.h"

PlannerWidget::PlannerWidget(QWidget *parent)
    : QStackedWidget(parent)
{
    geometricPlanning = new GeometricPlannerWidget(this);
    controlPlanning   = new ControlPlannerWidget(this);

    addWidget(geometricPlanning);
    addWidget(controlPlanning);

    // In python, we do self.setCurrentIndex(0 if isGeometric else 1).
    // The main window can do setCurrentIndex(...) accordingly.
}

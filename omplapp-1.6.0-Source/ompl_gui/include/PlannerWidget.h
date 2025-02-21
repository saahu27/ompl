// PlannerWidget.h
#ifndef PLANNERWIDGET_H
#define PLANNERWIDGET_H

#include <pinocchio/fwd.hpp>
#include <QStackedWidget>
#include "GeometricPlannerWidget.h"
#include "ControlPlannerWidget.h"

class PlannerWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit PlannerWidget(QWidget *parent = nullptr);

    GeometricPlannerWidget *geometricPlanning;
    ControlPlannerWidget *controlPlanning;
};

#endif // PLANNERWIDGET_H

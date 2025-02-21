// GeometricPlannerWidget.h
#ifndef GEOMETRICPLANNERWIDGET_H
#define GEOMETRICPLANNERWIDGET_H

#include "PlannerHelperWidget.h"
#include <QDoubleSpinBox>

class GeometricPlannerWidget : public PlannerHelperWidget
{
    Q_OBJECT
public:
    explicit GeometricPlannerWidget(QWidget *parent = nullptr);

    QDoubleSpinBox *timeLimit;
    QDoubleSpinBox *resolution;
};

#endif // GEOMETRICPLANNERWIDGET_H

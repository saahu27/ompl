// GeometricPlannerWidget.cpp
#include "GeometricPlannerWidget.h"
#include <QGridLayout>
#include <QLabel>

GeometricPlannerWidget::GeometricPlannerWidget(QWidget *parent)
    : PlannerHelperWidget("Geometric planning", parent)
{
    // We have a timeLimit double spinbox, resolution double spinbox
    QLabel *timeLabel = new QLabel("Time (sec.)", this);
    timeLimit = new QDoubleSpinBox(this);
    timeLimit->setRange(0, 10000);
    timeLimit->setSingleStep(1);
    timeLimit->setValue(10.0);

    QLabel *resLabel = new QLabel("Collision checking\nresolution", this);
    resLabel->setAlignment(Qt::AlignRight);
    resolution = new QDoubleSpinBox(this);
    resolution->setRange(0.001, 1.0);
    resolution->setSingleStep(0.002);
    resolution->setValue(0.01);
    resolution->setDecimals(3);

    // We'll place them in a row above or below the stackedWidget
    QGridLayout *lay = qobject_cast<QGridLayout*>(layout());
    if (!lay) return;

    int row = lay->rowCount();
    lay->addWidget(timeLabel, row, 0, Qt::AlignRight);
    lay->addWidget(timeLimit, row, 1);
    row++;
    lay->addWidget(resLabel, row, 0, Qt::AlignRight);
    lay->addWidget(resolution, row, 1);
}

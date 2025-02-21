// BoundsWidget.cpp
#include "BoundsWidget.h"
#include <QGridLayout>

BoundsWidget::BoundsWidget(QWidget *parent)
    : QWidget(parent)
{
    bounds_high = new BoundsBox("Upper bounds", this);
    bounds_low  = new BoundsBox("Lower bounds", this);
    resetButton = new QPushButton("Reset", this);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(bounds_high, 0, 0);
    layout->addWidget(bounds_low, 1, 0);
    layout->addWidget(resetButton, 2, 0, Qt::AlignRight);
    setLayout(layout);
}

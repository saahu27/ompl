// BoundsBox.cpp
#include "BoundsBox.h"

BoundsBox::BoundsBox(const QString &title, QWidget *parent)
    : QGroupBox(title, parent)
{
    QLabel *xlabel = new QLabel("X", this);
    QLabel *ylabel = new QLabel("Y", this);
    QLabel *zlabel = new QLabel("Z", this);

    posx_ = new QDoubleSpinBox(this);
    posx_->setRange(-1000, 1000);

    posy_ = new QDoubleSpinBox(this);
    posy_->setRange(-1000, 1000);

    posz_ = new QDoubleSpinBox(this);
    posz_->setRange(-1000, 1000);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(xlabel, 1, 0, Qt::AlignRight);
    layout->addWidget(ylabel, 2, 0, Qt::AlignRight);
    layout->addWidget(zlabel, 3, 0, Qt::AlignRight);
    layout->addWidget(posx_, 1, 1);
    layout->addWidget(posy_, 2, 1);
    layout->addWidget(posz_, 3, 1);
    setLayout(layout);

    connect(posx_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &BoundsBox::onValueChanged);
    connect(posy_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &BoundsBox::onValueChanged);
    connect(posz_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &BoundsBox::onValueChanged);
}

std::array<double,3> BoundsBox::getBounds() const
{
    return { posx_->value(), posy_->value(), posz_->value() };
}

void BoundsBox::setBounds(const std::array<double,3> &vals)
{
    posx_->setValue(vals[0]);
    posy_->setValue(vals[1]);
    posz_->setValue(vals[2]);
}

void BoundsBox::onValueChanged(double)
{
    emit valueChanged(getBounds());
}

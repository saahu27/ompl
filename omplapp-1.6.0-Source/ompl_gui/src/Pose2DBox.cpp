// Pose2DBox.cpp
#include "Pose2DBox.h"
#include <cmath>

Pose2DBox::Pose2DBox(const QString &title, QWidget *parent)
    : QGroupBox(title, parent)
{
    QLabel *xlabel = new QLabel("X", this);
    QLabel *ylabel = new QLabel("Y", this);
    QLabel *rotlabel = new QLabel("Rotation", this);

    posx_ = new QDoubleSpinBox(this);
    posx_->setRange(-1000, 1000);
    posx_->setSingleStep(1);

    posy_ = new QDoubleSpinBox(this);
    posy_->setRange(-1000, 1000);
    posy_->setSingleStep(1);

    rot_ = new QDoubleSpinBox(this);
    rot_->setRange(-180, 179); // as in python code
    rot_->setSingleStep(1);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(xlabel, 0, 0, Qt::AlignRight);
    layout->addWidget(ylabel, 1, 0, Qt::AlignRight);
    layout->addWidget(rotlabel, 2, 0, Qt::AlignRight);
    layout->addWidget(posx_, 0, 1);
    layout->addWidget(posy_, 1, 1);
    layout->addWidget(rot_, 2, 1);
    setLayout(layout);

    connect(posx_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose2DBox::onValueChanged);
    connect(posy_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose2DBox::onValueChanged);
    connect(rot_,  QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose2DBox::onValueChanged);
}

std::array<double,6> Pose2DBox::getPose() const
{
    // mimic the python code's [0,0, rot, x, y, 0]
    return {
        0.0,
        0.0,
        rot_->value(),
        posx_->value(),
        posy_->value(),
        0.0
    };
}

void Pose2DBox::setPose(const std::array<double,6> &pose)
{
    // we expect [0,0,rot, x,y,0]
    posx_->setValue(pose[3]);
    posy_->setValue(pose[4]);
    rot_->setValue(pose[2]);
}

void Pose2DBox::onValueChanged(double)
{
    emit valueChanged(getPose());
}

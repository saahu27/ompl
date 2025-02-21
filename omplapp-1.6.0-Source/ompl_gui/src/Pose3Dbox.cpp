// Pose3DBox.cpp
#include "Pose3DBox.h"
#include <cmath>

Pose3DBox::Pose3DBox(const QString &title, QWidget *parent)
    : QGroupBox(title, parent)
{
    QLabel *xlabel = new QLabel("X", this);
    QLabel *ylabel = new QLabel("Y", this);
    QLabel *zlabel = new QLabel("Z", this);

    QLabel *poslabel = new QLabel("Position", this);
    QLabel *rotlabel = new QLabel("Rotation", this);

    posx_ = new QDoubleSpinBox(this);
    posx_->setRange(-1000, 1000);
    posx_->setSingleStep(1);

    posy_ = new QDoubleSpinBox(this);
    posy_->setRange(-1000, 1000);
    posy_->setSingleStep(1);

    posz_ = new QDoubleSpinBox(this);
    posz_->setRange(-1000, 1000);
    posz_->setSingleStep(1);

    rotx_ = new QDoubleSpinBox(this);
    rotx_->setRange(-360, 360);
    rotx_->setSingleStep(1);

    roty_ = new QDoubleSpinBox(this);
    roty_->setRange(-360, 360);
    roty_->setSingleStep(1);

    rotz_ = new QDoubleSpinBox(this);
    rotz_->setRange(-360, 360);
    rotz_->setSingleStep(1);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(poslabel, 0, 1, Qt::AlignHCenter | Qt::AlignBottom);
    layout->addWidget(rotlabel, 0, 2, Qt::AlignHCenter | Qt::AlignBottom);

    layout->addWidget(xlabel, 1, 0, Qt::AlignRight);
    layout->addWidget(ylabel, 2, 0, Qt::AlignRight);
    layout->addWidget(zlabel, 3, 0, Qt::AlignRight);

    layout->addWidget(posx_, 1, 1);
    layout->addWidget(posy_, 2, 1);
    layout->addWidget(posz_, 3, 1);

    layout->addWidget(rotx_, 1, 2);
    layout->addWidget(roty_, 2, 2);
    layout->addWidget(rotz_, 3, 2);

    setLayout(layout);

    // connect changes
    connect(posx_,  QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose3DBox::onValueChanged);
    connect(posy_,  QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose3DBox::onValueChanged);
    connect(posz_,  QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose3DBox::onValueChanged);
    connect(rotx_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose3DBox::onValueChanged);
    connect(roty_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose3DBox::onValueChanged);
    connect(rotz_, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &Pose3DBox::onValueChanged);
}

std::array<double,6> Pose3DBox::getPose() const
{
    // [rotx, roty, rotz, posx, posy, posz]
    return {
        rotx_->value(),
        roty_->value(),
        rotz_->value(),
        posx_->value(),
        posy_->value(),
        posz_->value()
    };
}

void Pose3DBox::setPose(const std::array<double,6> &pose)
{
    rotx_->setValue(pose[0]);
    roty_->setValue(pose[1]);
    rotz_->setValue(pose[2]);
    posx_->setValue(pose[3]);
    posy_->setValue(pose[4]);
    posz_->setValue(pose[5]);
}

void Pose3DBox::onValueChanged(double)
{
    emit valueChanged(getPose());
}

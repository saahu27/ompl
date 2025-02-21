// Pose3DBox.h
#ifndef POSE3DBOX_H
#define POSE3DBOX_H

#include <QGroupBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <array>

class Pose3DBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit Pose3DBox(const QString &title, QWidget *parent = nullptr);

    // get/set pose as array [rotx, roty, rotz, posx, posy, posz]
    std::array<double,6> getPose() const;
    void setPose(const std::array<double,6> &pose);

signals:
    void valueChanged(const std::array<double,6> &pose);

private slots:
    void onValueChanged(double);

private:
    QDoubleSpinBox *posx_, *posy_, *posz_;
    QDoubleSpinBox *rotx_, *roty_, *rotz_;
};

#endif // POSE3DBOX_H

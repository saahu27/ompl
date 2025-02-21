// Pose2DBox.h
#ifndef POSE2DBOX_H
#define POSE2DBOX_H

#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <array>

class Pose2DBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit Pose2DBox(const QString &title, QWidget *parent = nullptr);

    // returns [0,0, rotation, x, y, 0]
    std::array<double,6> getPose() const;
    void setPose(const std::array<double,6> &pose);

signals:
    void valueChanged(const std::array<double,6> &pose);

private slots:
    void onValueChanged(double);

private:
    QDoubleSpinBox *posx_, *posy_, *rot_;
};

#endif // POSE2DBOX_H

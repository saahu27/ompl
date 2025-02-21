// BoundsBox.h
#ifndef BOUNDSBOX_H
#define BOUNDSBOX_H

#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QGridLayout>
#include <array>

class BoundsBox : public QGroupBox
{
    Q_OBJECT
public:
    explicit BoundsBox(const QString &title, QWidget *parent = nullptr);

    // get bounds as array [x,y,z]
    std::array<double,3> getBounds() const;
    void setBounds(const std::array<double,3> &vals);

signals:
    void valueChanged(const std::array<double,3> &vals);

private slots:
    void onValueChanged(double);

private:
    QDoubleSpinBox *posx_, *posy_, *posz_;
};

#endif // BOUNDSBOX_H

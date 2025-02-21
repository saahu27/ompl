// BoundsWidget.h
#ifndef BOUNDSWIDGET_H
#define BOUNDSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "BoundsBox.h"

class BoundsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BoundsWidget(QWidget *parent = nullptr);

    BoundsBox *bounds_high;
    BoundsBox *bounds_low;
    QPushButton *resetButton;
};

#endif // BOUNDSWIDGET_H

// SolveWidget.h
#ifndef SOLVEWIDGET_H
#define SOLVEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QSlider>
#include <QGridLayout>

class SolveWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SolveWidget(QWidget *parent = nullptr);

    QPushButton *solveButton;
    QPushButton *clearButton;
    QLabel *solvedLabel;
    QComboBox *explorationVizSelect;
    QCheckBox *animateCheck;
    QSlider *speedSlider;
};

#endif // SOLVEWIDGET_H

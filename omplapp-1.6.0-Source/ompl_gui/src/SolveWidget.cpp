// SolveWidget.cpp
#include "SolveWidget.h"

SolveWidget::SolveWidget(QWidget *parent)
    : QWidget(parent)
{
    solveButton = new QPushButton("Solve", this);
    clearButton = new QPushButton("Clear", this);
    solvedLabel = new QLabel(this);

    QLabel *explorationVizLabel = new QLabel("Show:", this);
    explorationVizSelect = new QComboBox(this);
    explorationVizSelect->addItem("none");
    explorationVizSelect->addItem("states");
    explorationVizSelect->addItem("states and edges");

    animateCheck = new QCheckBox("Animate", this);
    animateCheck->setChecked(true);

    QLabel *speedLabel = new QLabel("Speed:", this);
    speedSlider = new QSlider(Qt::Horizontal, this);
    speedSlider->setTickPosition(QSlider::TicksBothSides);
    speedSlider->setTickInterval(1);
    speedSlider->setSingleStep(1);
    speedSlider->setValue(1);
    speedSlider->setMaximum(11);
    speedSlider->setMaximumSize(200, 30);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(solveButton, 0, 0);
    layout->addWidget(clearButton, 0, 1);
    layout->addWidget(solvedLabel, 0, 2, Qt::AlignRight);
    layout->addWidget(explorationVizLabel, 0, 3, Qt::AlignRight);
    layout->addWidget(explorationVizSelect, 0, 4);
    layout->addWidget(animateCheck, 0, 5);
    layout->addWidget(speedLabel, 0, 6);
    layout->addWidget(speedSlider, 0, 7);
    setLayout(layout);
}

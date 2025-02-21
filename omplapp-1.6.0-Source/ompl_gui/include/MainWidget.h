// MainWidget.h
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QTabWidget>
#include "GLViewer.h"
#include "ProblemWidget.h"
#include "PlannerWidget.h"
#include "BoundsWidget.h"
#include "SolveWidget.h"

/**
 * @brief MainWidget replicates the structure of the Python code's MainWidget:
 * - GLViewer for 3D scene
 * - QTabWidget containing ProblemWidget, PlannerWidget, BoundsWidget
 * - SolveWidget at the bottom
 */
class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(const QList<QPair<QString, QString>> &robotTypes,
                        QWidget *parent = nullptr);

    GLViewer *glViewer;
    ProblemWidget *problemWidget;
    PlannerWidget *plannerWidget;
    BoundsWidget *boundsWidget;
    SolveWidget *solveWidget;
};

#endif // MAINWIDGET_H

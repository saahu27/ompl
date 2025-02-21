// PlannerHelperWidget.h
#ifndef PLANNERHELPERWIDGET_H
#define PLANNERHELPERWIDGET_H
#include <pinocchio/fwd.hpp>

#include <QGroupBox>
#include <QComboBox>
#include <QStackedWidget>
#include <QMap>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDebug>
#include <QVariant>

#include "PlannerRegistry.h"
#include "PlannerLists.h"
#include "PlannerParameterHelper.h" // include our helper module
#include <QDebug>

namespace ob = ompl::base;

/**
 * @brief A minimal port of the Python code's PlannerHelperWidget,
 *        which used the OMPL planner param dict. In Python, it calls
 *        e.g. og.planners.getPlanners(), then creates QWidgets for each param.
 *        We’ll just show a skeleton that you can populate with real planner param logic.
 */
class PlannerHelperWidget : public QGroupBox
{
    Q_OBJECT
public:
    explicit PlannerHelperWidget(const QString &title, QWidget *parent = nullptr);

    // In python, 'plannerSelect' is a QComboBox to pick which planner
    QComboBox *plannerSelect;
    QStackedWidget *stackedWidget;

    // A structure for storing planner parameter widgets
    // You might replicate python’s self.plannerList
    // e.g. vector of (plannerName, mapOfParameterName->widget)
    struct PlannerParam {
        QString plannerId;
        QMap<QString, QWidget*> paramWidgets;
    };
    QList<PlannerParam> plannerList;

    /**
     * @brief Populate the widget’s planner list based on the problem type.
     * @param isGeometric Set true to show geometric planners; false for control planners.
     *
     * This function clears any existing entries and queries OMPL’s PlannerRegistry for the
     * appropriate type. For each planner, it creates a simple page (here just a label
     * stating “No parameters”) and adds an entry to plannerSelect.
     */
    void populatePlannerList(bool isGeometric);
    
};

#endif // PLANNERHELPERWIDGET_H

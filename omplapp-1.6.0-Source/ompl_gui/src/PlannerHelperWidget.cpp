// PlannerHelperWidget.cpp
#include <pinocchio/fwd.hpp>
#include "PlannerHelperWidget.h"


PlannerHelperWidget::PlannerHelperWidget(const QString &title, QWidget *parent)
    : QGroupBox(title, parent)
{
    setFlat(true);
    plannerSelect = new QComboBox(this);
    stackedWidget = new QStackedWidget(this);

    // By default, you might populate with geometric planners.
    populatePlannerList(true);

    // When the selection changes, show the corresponding parameter page.
    connect(plannerSelect, QOverload<int>::of(&QComboBox::currentIndexChanged),
            stackedWidget, &QStackedWidget::setCurrentIndex);

    // Layout for the entire widget.
    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(new QLabel("Planner:"), 0, 0, Qt::AlignRight);
    mainLayout->addWidget(plannerSelect, 0, 1);
    mainLayout->addWidget(stackedWidget, 1, 0, 1, 2);
    setLayout(mainLayout);
}

void PlannerHelperWidget::populatePlannerList(bool isGeometric)
{
    static bool plannersRegistered = false;
    if (!plannersRegistered) {
        registerGeometricPlanners();
        registerControlPlanners();
        plannersRegistered = true;
    }
    
    // Clear any existing entries.
    plannerList.clear();
    plannerSelect->clear();
    while (QWidget* widget = stackedWidget->widget(0))
    {
        stackedWidget->removeWidget(widget);
        widget->deleteLater();
    }

    AllPlannerParams allParams = getAllPlannerParameters();

    if (isGeometric)
    {
        auto &registry = ompl::geometric::PlannerRegistry::getInstance();
        for (const auto &entry : registry.getPlanners())
        {
            PlannerParam param;
            QString plannerId = QString::fromStdString(entry.first);
            param.plannerId = plannerId;
            
            // Create a page for this planner’s options.
            QGroupBox *page = new QGroupBox(plannerId + " options", this);
            QGridLayout *layout = new QGridLayout(page);
            int row = 0;
            
            // Get parameter definitions for this planner.
            // (Assume that you have already built a mapping of planner IDs to parameter maps.)
            if (allParams.contains(plannerId))
            {
                const PlannerParamsMap &paramMap = allParams[plannerId];
                for (auto it = paramMap.constBegin(); it != paramMap.constEnd(); ++it)
                {
                    QString paramName = it.key();
                    PlannerParamDefinition def = it.value();
                    QLabel *label = new QLabel(def.description, page);
                    QWidget *widget = nullptr;
                    
                    switch (def.type)
                    {
                        case ParamType::BOOL:
                        {
                            QCheckBox *cb = new QCheckBox(page);
                            cb->setChecked(def.defaultValue.toBool());
                            widget = cb;
                            break;
                        }
                        case ParamType::INT:
                        {
                            QSpinBox *spin = new QSpinBox(page);
                            spin->setRange(static_cast<int>(def.minValue), static_cast<int>(def.maxValue));
                            spin->setSingleStep(static_cast<int>(def.step));
                            spin->setValue(def.defaultValue.toInt());
                            widget = spin;
                            break;
                        }
                        case ParamType::DOUBLE:
                        {
                            QDoubleSpinBox *dspin = new QDoubleSpinBox(page);
                            dspin->setRange(def.minValue, def.maxValue);
                            dspin->setSingleStep(def.step);
                            dspin->setValue(def.defaultValue.toDouble());
                            widget = dspin;
                            break;
                        }
                        case ParamType::ENUM:
                        {
                            QComboBox *combo = new QComboBox(page);
                            combo->addItems(def.enumValues);
                            combo->setCurrentIndex(def.defaultValue.toInt());
                            widget = combo;
                            break;
                        }
                    }
                    
                    if (widget)
                    {
                        layout->addWidget(label, row, 0, Qt::AlignRight);
                        layout->addWidget(widget, row, 1);
                        // Save the widget pointer so you can read its value later.
                        param.paramWidgets.insert(paramName, widget);
                        row++;
                    }
                }
            }
            else
            {
                // If no parameters are defined, add a placeholder.
                QLabel *placeholder = new QLabel("No parameters", page);
                layout->addWidget(placeholder, 0, 0);
            }
            
            page->setLayout(layout);
            stackedWidget->addWidget(page);
            plannerList.append(param);
            plannerSelect->addItem(plannerId);
            qDebug() << "Added planner" << plannerId 
                     << "with" << (allParams.contains(plannerId) ? allParams[plannerId].size() : 0) 
                     << "parameters";
        }
    }
    else
    {
        // Query the control planner registry.
        auto &registry = ompl::control::PlannerRegistry::getInstance();
        for (const auto &entry : registry.getPlanners())
        {
            PlannerParam param;
            param.plannerId = QString::fromStdString(entry.first);

            QGroupBox *group = new QGroupBox(QString::fromStdString(entry.first) + " options", this);
            QGridLayout *groupLayout = new QGridLayout(group);
            QLabel *label = new QLabel("No parameters", group);
            groupLayout->addWidget(label, 0, 0);
            group->setLayout(groupLayout);

            stackedWidget->addWidget(group);
            plannerList.append(param);
            plannerSelect->addItem(QString::fromStdString(entry.first));
            //plannerSelect->addItem(QString::fromStdString(param.plannerId));
        }
    }
}
#ifndef PLANNERPARAMETERHELPER_H
#define PLANNERPARAMETERHELPER_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QVariant>

// Instead of trying to use OMPL’s (internal) ParamContainer,
// we define our own parameter definition types.

enum class ParamType { BOOL, ENUM, INT, DOUBLE };

struct PlannerParamDefinition {
  QString description;    // Human-readable description
  ParamType type;         // The type (BOOL, ENUM, INT, DOUBLE)
  QStringList enumValues; // For ENUM types (list of possible string values)
  double minValue;        // For INT/DOUBLE types
  double maxValue;        // For INT/DOUBLE types
  double step;            // For INT/DOUBLE types
  QVariant defaultValue;  // The default value
};

using PlannerParamsMap = QMap<QString, PlannerParamDefinition>;

// A mapping from planner ID (for example, "RRTstar") to its parameter map.
using AllPlannerParams = QMap<QString, PlannerParamsMap>;

// This function returns the mapping for every planner in OMPL that you want to support.
// You must fill in the details for each planner (either by hand or by generating the mapping).
AllPlannerParams getAllPlannerParameters();

#endif // PLANNERPARAMETERHELPER_H

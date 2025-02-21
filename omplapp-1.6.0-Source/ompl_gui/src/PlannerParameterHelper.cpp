#include "PlannerParameterHelper.h"
#include <QDebug>

AllPlannerParams getAllPlannerParameters()
{
    AllPlannerParams allParams;

    // --- Geometric planners ---

    // AITstar
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;
        
        def.description = "Find approximate solutions";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("find_approximate_solutions", def);

        def.description = "Rewire factor (connection radius multiplier)";
        def.type = ParamType::DOUBLE;
        def.minValue = 1.0;
        def.maxValue = 3.0;
        def.step = 0.01;
        def.defaultValue = 1.00;
        params.insert("rewire_factor", def);

        def.description = "Samples per batch";
        def.type = ParamType::INT;
        def.minValue = 1;
        def.maxValue = 100000;
        def.step = 1;
        def.defaultValue = 100;
        params.insert("samples_per_batch", def);

        def.description = "Use k-nearest neighbors (vs. r-disc)";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("use_k_nearest", def);

        def.description = "Use Graph pruning";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("prune", def);

        def.description = "Set max num goals";
        def.type = ParamType::INT;
        def.minValue = 1;
        def.maxValue = 1000;
        def.step = 1;
        def.defaultValue = 1;
        params.insert("max_goal_samples", def);

        allParams.insert("AITstar", params);
    }

    // ABITstar
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "Delay rewiring to first solution";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("delay_rewiring", def);

        def.description = "Drop unconnected samples on prune";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("drop_samples_on_prune", def);

        def.description = "Find approximate solutions";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("find_approximate_solutions", def);

        def.description = "Inflation scaling parameter";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1000.0;
        def.step = 0.1;
        def.defaultValue = 10.0;
        params.insert("inflation_scaling_parameter", def);

        def.description = "Initial inflation factor";
        def.type = ParamType::DOUBLE;
        def.minValue = 1.0;
        def.maxValue = 1000000.0;
        def.step = 0.1;
        def.defaultValue = 100000.0;
        params.insert("initial_inflation_factor", def);

        def.description = "Prune threshold as fractional cost change";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.01;
        def.defaultValue = 0.05;
        params.insert("prune_threshold_fraction", def);


        def.description = "Rewire factor";
        def.type = ParamType::DOUBLE;
        def.minValue = 1.0;
        def.maxValue = 3.0;
        def.step = 0.01;
        def.defaultValue = 1.1;
        params.insert("rewire_factor", def);

        def.description = "Samples per batch";
        def.type = ParamType::INT;
        def.minValue = 1;
        def.maxValue = 100000;
        def.step = 1;
        def.defaultValue = 100;
        params.insert("samples_per_batch", def);

        def.description = "Stop on each solution improvement";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("stop_on_soln_improvement", def);

        def.description = "Truncation scaling parameter";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1000.0;
        def.step = 0.1;
        def.defaultValue = 10.0;
        params.insert("truncation_scaling_parameter", def);

        def.description = "Use graph pruning";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("prune", def);

        def.description = "Use just-in-time sampling";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("just_in_time_sampling", def);

        def.description = "Use k nearest neighbors";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("use_k_nearest", def);

        def.description = "Use strict queue ordering";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("strict_queue_ordering", def);

        allParams.insert("ABITstar", params);

    }

    // BITstar
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;
        
        def.description = "Delay rewiring to first solution";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("delay_rewiring", def);

        def.description = "Drop unconnected samples on prune";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("drop_samples_on_prune", def);

        def.description = "Find approximate solutions";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("find_approximate_solutions", def);

        def.description = "Prune threshold as fractional cost change";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.01;
        def.defaultValue = 0.05;
        params.insert("prune_threshold_fraction", def);

        def.description = "Rewire factor";
        def.type = ParamType::DOUBLE;
        def.minValue = 1.0;
        def.maxValue = 3.0;
        def.step = 0.01;
        def.defaultValue = 1.1;
        params.insert("rewire_factor", def);

        def.description = "Samples per batch";
        def.type = ParamType::INT;
        def.minValue = 1;
        def.maxValue = 100000;
        def.step = 1;
        def.defaultValue = 100;
        params.insert("samples_per_batch", def);

        def.description = "Stop on each solution improvement";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("stop_on_soln_improvement", def);

        def.description = "Use Graph pruning";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("prune", def);

        def.description = "Use just in time sampling";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("just_in_time_sampling", def);

        def.description = "Use k nearest neighbors";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("use_k_nearest", def);

        def.description = "Use strict queue ordering";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("strict_queue_ordering", def);


        allParams.insert("BITstar", params);
    }

    // RRTstar
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "Delay collision checking";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("delay_collision_checking", def);

        def.description = "Focus search";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("focus_search", def);

        def.description = "Goal bias probability";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.05;
        def.defaultValue = 0.05;
        params.insert("goal_bias", def);

        def.description = "Informed sampling";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("informed_sampling", def);

        def.description = "New state rejection";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("new_state_rejection", def);

        def.description = "Number sampling attempts";
        def.type = ParamType::INT;
        def.minValue = 1;
        def.maxValue = 100;
        def.step = 1;
        def.defaultValue = 100;
        params.insert("num_sampling_attempts", def);

        def.description = "Ordered sampling";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("ordered_sampling", def);

        def.description = "Ordering batch size";
        def.type = ParamType::INT;
        def.minValue = 1;
        def.maxValue = 1000000;
        def.step = 1;
        def.defaultValue = 1;
        params.insert("ordering_batch_size", def);

        def.description = "Prune threshold";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.01;
        def.defaultValue = 0.05;
        params.insert("prune_threshold", def);

        def.description = "Pruned measure";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("pruned_measure", def);

        def.description = "Range";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 10000.0;
        def.step = 1;
        def.defaultValue = 0.0;
        params.insert("range", def);

        def.description = "Rewire factor";
        def.type = ParamType::DOUBLE;
        def.minValue = 1.0;
        def.maxValue = 3.0;
        def.step = 0.01;
        def.defaultValue = 1.1;
        params.insert("rewire_factor", def);

        def.description = "Sample rejection";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("sample_rejection", def);

        def.description = "Tree pruning";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("tree_pruning", def);

        def.description = "Use admissible heuristics";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("use_admissible_heuristics", def);

        def.description = "Use k nearest";
        def.type = ParamType::BOOL;
        def.defaultValue = true;
        params.insert("use_k_nearest", def);

        allParams.insert("RRTstar", params);
    }

    // KPIECE1
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "Border fraction";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.05;
        def.defaultValue = 0.9;
        params.insert("border_fraction", def);

        def.description = "Range";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 100.0;
        def.step = 0.1;
        def.defaultValue = 0.0;
        params.insert("range", def);

        def.description = "Goal bias probability";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.05;
        def.defaultValue = 0.05;
        params.insert("goal_bias", def);

        allParams.insert("KPIECE1", params);
    }

    // LBTRRT
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "Maximum extension length";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 10.0;
        def.step = 0.1;
        def.defaultValue = 0.0;
        params.insert("range", def);

        def.description = "Epsilon (acceptable edge improvement)";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 10.0;
        def.step = 0.1;
        def.defaultValue = 0.4;
        params.insert("epsilon", def);

        def.description = "Goal bias";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.05;
        def.defaultValue = 0.05;
        params.insert("goal_bias", def);

        allParams.insert("LBTRRT", params);
    }

    // TRRT
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "Goal bias";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.05;
        def.defaultValue = 0.05;
        params.insert("goal_bias", def);

        def.description = "Maximum extension length";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 10.0;
        def.step = 0.1;
        def.defaultValue = 0.0;
        params.insert("range", def);

        def.description = "Temperature change factor";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.1;
        def.maxValue = 10.0;
        def.step = 0.1;
        def.defaultValue = 0.1;
        params.insert("temp_change_factor", def);

        allParams.insert("TRRT", params);
    }

    // RRTConnect
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;
        
        def.description = "Maximum extension length";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 10.0;
        def.step = 0.1;
        def.defaultValue = 0.0;
        params.insert("range", def);

        def.description = "Intermediate states";
        def.type = ParamType::BOOL;
        def.defaultValue = false;
        params.insert("intermediate_states", def);

        allParams.insert("RRTConnect", params);
    }

    // PRM
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "Max nearest neighbors";
        def.type = ParamType::INT;
        def.minValue = 1;
        def.maxValue = 100;
        def.step = 1;
        def.defaultValue = 10;
        params.insert("max_nearest_neighbors", def);

        allParams.insert("PRM", params);
    }

    // SPARS
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "Dense delta fraction";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.05;
        def.defaultValue = 0.1;
        params.insert("dense_delta_fraction", def);

        def.description = "Max failures";
        def.type = ParamType::INT;
        def.minValue = 1;
        def.maxValue = 100;
        def.step = 1;
        def.defaultValue = 5;
        params.insert("max_failures", def);

        def.description = "Sparse delta fraction";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.05;
        def.defaultValue = 0.25;
        params.insert("sparse_delta_fraction", def);


        def.description = "Stretch factor";
        def.type = ParamType::DOUBLE;
        def.minValue = 1.0;
        def.maxValue = 5.0;
        def.step = 0.1;
        def.defaultValue = 3.0;
        params.insert("stretch_factor", def);

        allParams.insert("SPARS", params);
    }

    // --- Control planners ---

    // RRT (control)
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "State validity check resolution";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.01;
        def.maxValue = 1.0;
        def.step = 0.01;
        def.defaultValue = 0.2;
        params.insert("state_validity_check_resolution", def);

        def.description = "Goal bias probability";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 1.0;
        def.step = 0.05;
        def.defaultValue = 0.05;
        params.insert("goal_bias", def);

        allParams.insert("RRT", params);
    }

    // SST (control)
    {
        PlannerParamsMap params;
        PlannerParamDefinition def;

        def.description = "Selection radius";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 5.0;
        def.step = 0.01;
        def.defaultValue = 0.5;
        params.insert("selection_radius", def);

        def.description = "Pruning radius";
        def.type = ParamType::DOUBLE;
        def.minValue = 0.0;
        def.maxValue = 5.0;
        def.step = 0.01;
        def.defaultValue = 0.2;
        params.insert("pruning_radius", def);

        allParams.insert("SST", params);
    }

    qDebug() << "Created AllPlannerParams mapping with" << allParams.size() << "entries.";
    return allParams;
}
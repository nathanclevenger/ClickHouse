#include <Processors/QueryPlan/Optimizations/QueryPlanOptimizationSettings.h>
#include <Core/Settings.h>
#include <Interpreters/Context.h>

namespace DB
{

QueryPlanOptimizationSettings QueryPlanOptimizationSettings::fromSettings(const Settings & from)
{
    QueryPlanOptimizationSettings settings;
    settings.optimize_plan = from.query_plan_enable_optimizations;
    settings.max_optimizations_to_apply = from.query_plan_max_optimizations_to_apply;
    settings.filter_push_down = from.query_plan_filter_push_down;
    settings.distinct_in_order = from.optimize_distinct_in_order;
    settings.read_in_order = from.optimize_read_in_order && from.query_plan_read_in_order;
    settings.aggregation_in_order = from.optimize_aggregation_in_order && from.query_plan_aggregation_in_order;
    settings.remove_redundant_sorting = from.query_plan_remove_redundant_sorting;
    settings.remove_redundant_distinct = from.query_plan_remove_redundant_distinct;
    return settings;
}

QueryPlanOptimizationSettings QueryPlanOptimizationSettings::fromContext(ContextPtr from)
{
    return fromSettings(from->getSettingsRef());
}

}

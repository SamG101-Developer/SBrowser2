#pragma once
#include "css/css_animation_worklet/animation_worklet_global_scope.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_DETAIL_ANIMATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_DETAIL_ANIMATION_INTERNALS_HPP

#include "ext/boolean.ixx"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(css/css_animation_worklet)

namespace css::css_animation_worklet {class animation_worklet_global_scope;}


namespace css::detail
{
    auto is_stateful_animator(
            const animator_definition_t& animator)
            -> ext::boolean;

    auto is_stateful_animator_instance(
            const animator_instance_t& animator_instance)
            -> ext::boolean;

    auto create_new_animator_instance(
            ext::string&& name,
            ext::map<ext::string, ext::any>&& options,
            css_animation_worklet::animation_worklet_global_scope* scope)
            -> animator_instance_t;

    auto run_animators(
            css_animation_worklet::animation_worklet_global_scope* scope)
            -> void;

    auto remove_animator_instance(
            const animator_instance_t& animator_instance,
            css_animation_worklet::animation_worklet_global_scope* scope)
            -> void;

    auto migrate_animator_instance(
            const animator_instance_t& animator_instance,
            css_animation_worklet::animation_worklet_global_scope* source_worklet_global_scope,
            css_animation_worklet::animation_worklet_global_scope* destination_worklet_global_scope)
            -> void;
}


struct css::detail::animator_definition_t
{
    ext::string animator_name;
    animator_instance_constructor_t class_constructor;
    ext::function<void(ext::number<double> current_time, const animator_effect_t& effect)> animate_function;
    ext::function<void()> state_function;
    ext::boolean stateful_flag;
};


struct css::detail::document_animator_definition_t
{
    ext::boolean stateful_flag;
    ext::boolean invalid;
};


struct css::detail::animator_effect_t
{
    ext::number<double> local_time;
    ext::number<double> start_delay;
    ext::number<double> end_delay;
    ext::string fill_mode;
    ext::number<int> iteration_start;
    ext::number<int> iteration_count;
    ext::number<double> iteration_duration;
    ext::string direction;
    ext::function<void()> timing_function;
};


struct css::detail::animator_instance_t
{
    ext::string animator_name;
    ext::boolean frame_requested_flag;
    ext::boolean sync_requested_flag;
    animator_effect_t effect;
    ext::number<double> animator_current_time;
    // TODO : animator_timeline;
    ext::map<ext::string, ext::any> options;

    animator_definition_t* animator_definition;
};


struct css::detail::worklet_animator_definition_t
{
    ext::string animation_animator_name;
    ext::map<ext::string, ext::any> serialized_options;
    animator_instance_t animator_instance;
};


struct css::detail::animation_worklet_global_scope_t
{
    ext::map<ext::string, std::unique_ptr<animator_definition_t>> animator_definitions;
    ext::vector<std::unique_ptr<animator_instance_t>> animator_instance_set;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET_DETAIL_ANIMATION_INTERNALS_HPP

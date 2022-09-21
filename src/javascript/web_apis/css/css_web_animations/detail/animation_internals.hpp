#pragma once
#include "css/css_web_animations/animation_effect_private.hpp"
#include "css/css_web_animations/animation_private.hpp"
#include "css/css_web_animations/animation_timeline_private.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DETAIL_ANIMATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DETAIL_ANIMATION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/functional.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/optional.hpp"
#include "ext/pimpl.hpp"
#include "ext/promise.hpp"
#include "ext/vector.hpp"
#include "ext/stack.hpp"
#include INCLUDE_INNER_TYPES(css)
#include INCLUDE_INNER_TYPES(css/css_web_animations)
#include INCLUDE_INNER_TYPES(hr_time)

namespace dom::nodes {class document;}
namespace dom::nodes {class element;}

DECLARE_PRIVATE_CLASS(css::css_web_animations, animation_timeline)
DECLARE_PRIVATE_CLASS(css::css_web_animations, animation)
DECLARE_PRIVATE_CLASS(css::css_web_animations, animation_effect)
DECLARE_PRIVATE_CLASS(css::css_web_animations, document_timeline)
DECLARE_PRIVATE_CLASS(css::css_web_animations, keyframe_effect)


namespace css::detail
{
    auto is_inactive_timeline(
            const css_web_animations::animation_timeline_private& timeline)
            -> ext::boolean;

    auto is_monotonically_increasing(
            const css_web_animations::animation_timeline_private& timeline)
            -> ext::boolean;

    auto update_animations_and_send_events(
            dom::nodes::document* document,
            hr_time::dom_high_res_time_stamp)
            -> void;

    auto set_timeline_of_animation(
            css_web_animations::animation_private& animation,
            css_web_animations::animation_timeline_private& timeline)
            -> void;

    auto set_associated_effect_of_animation(
            css_web_animations::animation_private& animation,
            const css_web_animations::animation_timeline_private& timeline)
            -> void;

    auto current_time(
            const css_web_animations::animation_private& animation)
            -> ext::number<int>;

    auto local_time(
            const css_web_animations::animation_private& animation)
            -> ext::number<int>;

    auto document_for_timing(
            const css_web_animations::animation_private& animation)
            -> dom::nodes::document*;

    auto reset_animations_pending_tasks(
            css_web_animations::animation_private& animation)
            -> void;

    auto silently_set_current_time_of_animation(
            css_web_animations::animation_private& animation,
            time_value_t seek_time)
            -> void;

    auto set_current_time_of_animation(
            css_web_animations::animation_private& animation,
            time_value_t seek_time)
            -> void;

    auto play_animation(
            const css_web_animations::animation_private& animation,
            ext::boolean auto_rewind)
            -> void;

    auto pause_animation(
            const css_web_animations::animation_private& animation)
            -> void;

    auto update_animations_finished_state(
            const css_web_animations::animation_private& animation,
            ext::boolean did_seek)
            -> void;

    auto finish_animation(
            const css_web_animations::animation_private& animation)
            -> void;

    auto cancel_animation(
            const css_web_animations::animation_private& animation)
            -> void;

    auto set_playback_rate(
            css_web_animations::animation_private& animation)
            -> void;

    auto effective_playback_rate(
            const css_web_animations::animation_private& animation)
            -> ext::number<int>;

    auto apply_any_pending_playback_rate(
            css_web_animations::animation_private& animation)
            -> void;
    auto seamlessly_update_playback_rate_of_animation(
            css_web_animations::animation_private& animation)
            -> void;

    auto reverse_animation(
            css_web_animations::animation_private& animation)
            -> void;

    auto animation_play_state(
            const css_web_animations::animation_private& animation)
            -> animation_play_state_t;

    auto commit_computed_styles(
            const css_web_animations::animation_private& animation)
            -> void;

    auto is_animation_replaceable(
            const css_web_animations::animation_private& animation)
            -> ext::boolean;

    auto remove_replace_animations(
            dom::nodes::document* document)
            -> void;

    auto convert_animation_time_to_timeline_time(
            time_value_t time)
            -> time_value_t;

    auto convert_timeline_time_to_origin_relative_time(
            time_value_t time)
            -> time_value_t;

    auto is_effect_Associated_with_timeline(
            const css_web_animations::animation_effect_private& effect)
            -> ext::boolean;

    auto animation_direction(
            const css_web_animations::animation_effect_private& effect)
            -> animation_effect_direction_t;

    auto before_active_boundary_time(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto active_after_boundary_time(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto effect_phase(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto fill_mode(
            const css_web_animations::animation_effect_private& effect)
            -> animation_effect_fill_mode_t;

    auto convert_local_time_to_iteration_progress(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto active_duration(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto active_time(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto end_time(
            const css_web_animations::animation_private& effect)
            -> ext::number<int>;

    auto end_time(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto overall_progress(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto simple_iteration_progress(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto current_iteration(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto directed_progress(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto transformed_progress(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto iteration_progress(
            const css_web_animations::animation_effect_private& effect)
            -> ext::number<int>;

    auto update_timing_properties_of_animation_effect(
            css_web_animations::animation_effect_private& effect,
            ext::map<ext::string, ext::any>&& options)
            -> void;

    auto target_element(
            const css_web_animations::keyframe_effect_private& keyframe_effect)
            -> dom::nodes::element*;

    auto target_pseudo_selector(
            const css_web_animations::keyframe_effect_private& keyframe_effect)
            -> pseudo_element_t;

    auto effect_values(
            const abstract_property_t& keyframe_effect)
            -> keyframe_t;

    auto effect_values(
            const keyframe_t& keyframe_effect)
            -> keyframe_t;

    auto compute_property_value(
            const abstract_property_t& property,
            ext::string&& value,
            dom::nodes::element* element)
            -> ext::string;

    auto produce_missing_keyframe_offsets(
            ext::vector_view<keyframe_t> keyframes)
            -> ext::vector<keyframe_t>;

    auto produce_computed_keyframes(
            const css_web_animations::keyframe_effect_private& keyframe_effect)
            -> ext::vector<keyframe_t>;

    auto relative_composite_order(
            const css_web_animations::keyframe_effect_private& keyframe_effect_a,
            const css_web_animations::keyframe_effect_private& keyframe_effect_b,
            effect_stack_t& keyframe_stack)
            -> void;

    auto composited_value(
            const abstract_property_t& keyframe_stack)
            -> ext::number<double>;

    auto composited_value(
            const effect_stack_t& keyframe_stack)
            -> ext::number<double>;

    auto convert_animation_property_name_to_idl_attribute_name(
            ext::string_view property_name)
            -> ext::string;

    auto convert_idl_attribute_name_to_animation_property_name(
            ext::string_view property_name)
            -> ext::string;

    auto check_completion_record(
            /* TODO */)
            -> void;

    auto process_keyframes_argument(
            void* object)
            -> ext::vector<keyframe_t>;
}


struct css::detail::keyframe_t
{
    ext::map<ext::number<double>, ext::number<double>> values;
    ext::function<ext::number<double>()> timing_function;
    keyframe_operation_t keyframe_specific_composite_operation;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DETAIL_ANIMATION_INTERNALS_HPP

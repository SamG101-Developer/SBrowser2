#pragma once
#include "ext/number.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DETAIL_ANIMATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DETAIL_ANIMATION_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/optional.hpp"
#include "ext/promise.hpp"
#include "ext/functional.hpp"
#include USE_INNER_TYPES(css/css_web_animations)
#include USE_INNER_TYPES(hr_time)

namespace dom::nodes {class document;}


namespace css::detail
{
    auto is_inactive_timeline(
            const timeline_t& timeline)
            -> ext::boolean;

    auto is_monotonically_increasing(
            const timeline_t& timeline)
            -> ext::boolean;

    auto update_animations_and_send_events(
            dom::nodes::document* document,
            hr_time::dom_high_res_time_stamp)
            -> void;

    auto set_timeline_of_animation(
            animation_t& animation,
            const timeline_t& timeline)
            -> void;

    auto set_associated_effect_of_animation(
            animation_t& animation,
            const timeline_t& timeline)
            -> void;

    auto reset_animations_pending_tasks(
            animation_t& animation)
            -> void;

    auto silently_set_current_time_of_animation(
            animation_t& animation,
            time_value_t seek_time)
            -> void;

    auto set_current_time_of_animation(
            animation_t& animation,
            time_value_t seek_time)
            -> void;

    auto play_animation(
            const animation_t& animation,
            ext::boolean auto_rewind)
            -> void;

    auto pause_animation(
            const animation_t& animation)
            -> void;

    auto update_animations_finished_state(
            const animation_t animation,
            ext::boolean did_seek)
            -> void;

    auto finish_animation(
            const animation_t& animation)
            -> void;

    auto cancel_animation(
            const animation_t& animation)
            -> void;

    auto set_playback_rate(
            animation_t& animation)
            -> void;

    auto effective_playback_rate(
            const animation_t& animation)
            -> ext::number<int>;

    auto apply_any_pending_playback_rate(
            animation_t& animation)
            -> void;
    auto seamlessly_update_playback_rate_of_animation(
            animation_t& animation)
            -> void;

    auto reverse_animation(
            animation_t& animation)
            -> void;

    auto animation_play_state(
            const animation_t& animation)
            -> animation_play_state_t;

    auto convert_animation_time_to_timeline_time(
            time_value_t time)
            -> time_value_t;

    auto convert_timeline_time_to_origin_relative_time(
            time_value_t time)
            -> time_value_t;

    auto is_effect_Associated_with_timeline(
            const animation_effect_t& effect)
            -> ext::boolean;

    auto animation_direction(
            const animation_effect_t& effect)
            -> animation_effect_direction_t;

    auto before_active_boundary_time(
            const animation_effect_t& effect)
            -> ext::number<int>;

    auto active_after_boundary_time(
            const animation_effect_t& effect)
            -> ext::number<int>;

    auto effect_phase(
            const animation_effect_t& effect)
            -> ext::number<int>;
}


struct css::detail::timeline_t
{
    virtual auto current_time() -> ext::optional<time_value_t>;
    virtual auto convert_timeline_to_origin_relative_time() -> time_value_t;
    dom::nodes::document* document;

    auto set_current_time(time_value_t time)
    {m_previous_time = m_current_time; m_current_time = time;};

protected:
    ext::optional<time_value_t> m_current_time;
    ext::optional<time_value_t> m_previous_time;
};


struct css::detail::document_timeline_t
        : public timeline_t
{
    auto current_time() -> ext::optional<time_value_t> override;
};


struct css::detail::animation_t
{
    std::unique_ptr<animation_effect_t> animation_effect;
    std::unique_ptr<timeline_t> timeline;
    auto current_time() -> time_value_t;

    _EXT_NODISCARD auto document_for_timing() const -> dom::nodes::document* {return timeline ? timeline->document : nullptr;}
    _EXT_NODISCARD auto associated_effect_end() const {return animation_effect ? animation_effect->end_time : 0;}
    _EXT_NODISCARD auto local_time() const;

    ext::optional<time_value_t> start_time;
    ext::optional<time_value_t> hold_time;

    ext::promise<> current_finished_promise;

    ext::number<int> playback_rate;
    ext::number<int> pending_playback_rate;
};


struct css::detail::animation_effect_t
{
    ext::pair<ext::number<int>, ext::number<int>> active_internal;
    ext::number<int> start_delay;

    ext::number<int> end_delay;

    auto active_duration() const -> ext::number<int> {return ext::abs(active_internal.second - active_internal.first);}
    auto end_time() const -> ext::number<int>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_DETAIL_ANIMATION_INTERNALS_HPP

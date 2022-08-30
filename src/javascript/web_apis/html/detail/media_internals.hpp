#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MEDIA_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MEDIA_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/promise.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(url)
namespace html::elements {class html_media_element;}
namespace html::elements {class html_video_element;}


namespace html::detail
{
    auto poster_frame(
            html::elements::html_video_element* element)
            -> auto; // TODO : return type

    auto media_element_load_algorithm(
            html::elements::html_media_element* element)
            -> void;

    auto resource_selection_algorithm(
            html::elements::html_media_element* element)
            -> void;

    auto dedicated_media_source_failure_steps(
            ext::vector<ext::promise<>>& promises)
            -> void;

    auto verify_media_response(
            const fetch::detail::response_t& response,
            html::elements::html_media_element* resource,
            const ext::any& byte_range)
            -> ext::boolean;

    auto resource_fetch_algorithm(
            html::elements::html_media_element* element,
            const url::detail::url_t& url)
            -> void;

    auto media_data_processing_steps_list(
            html::elements::html_media_element* element)
            -> void;

    auto forget_media_element_media_resource_specific_tracks(
            html::elements::html_media_element* element)
            -> void;

    auto earliest_possible_position(
            html::elements::html_media_element* element)
            -> ext::number<double>;

    auto when_network_state_changes(
            html::elements::html_media_element* element,
            const ext::number<ushort>& previous_ready_state,
            const ext::number<ushort>& new_ready_state)
            -> void;

    auto when_current_playback_position_at_end(
            html::elements::html_media_element* element)
            -> void;

    auto is_blocked_media_element(
            html::elements::html_media_element* element)
            -> ext::boolean;

    auto is_potentially_playing(
            html::elements::html_media_element* element)
            -> ext::boolean;

    auto is_eligible_for_autoplay(
            html::elements::html_media_element* element)
            -> ext::boolean;

    auto is_allowed_to_play(
            html::elements::html_media_element* element)
            -> ext::boolean;

    auto has_ended_playback(
            html::elements::html_media_element* element)
            -> ext::boolean;

    auto has_stopped_due_to_errors(
            html::elements::html_media_element* element)
            -> ext::boolean;

    auto has_paused_for_use_interaction(
            html::elements::html_media_element* element)
            -> ext::boolean;

    auto has_paused_for_in_band_content(
            html::elements::html_media_element* element)
            -> ext::boolean;

    auto take_pending_play_promises(
            html::elements::html_media_element* element)
            -> ext::vector<ext::promise<>>;

    auto resolve_pending_play_promises(
            html::elements::html_media_element* element)
            -> void;

    auto reject_pending_play_promises(
            html::elements::html_media_element* element)
            -> void;

    auto notify_about_playing(
            html::elements::html_media_element* element)
            -> void;

    auto internal_play_steps(
            html::elements::html_media_element* element)
            -> void;

    auto internal_pause_steps(
            html::elements::html_media_element* element)
            -> void;

    auto direction_of_playback(
            html::elements::html_media_element* element)
            -> media_playback_direction_t;

    auto time_marches_on(
            html::elements::html_media_element* element)
            -> void;

    auto seek(
            html::elements::html_media_element* element,
            const ext::number<double>& new_playback_position,
            ext::boolean&& approximate_for_speed_flag)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MEDIA_INTERNALS_HPP

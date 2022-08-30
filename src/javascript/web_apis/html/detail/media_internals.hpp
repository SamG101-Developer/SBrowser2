#pragma once
#include "html/basic_media/text_track.hpp"
#include "html/basic_media/text_track_cue.hpp"
#include "html/elements/html_track_element.hpp"
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MEDIA_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MEDIA_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/promise.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(url)

namespace html::basic_media {class text_track;}
namespace html::basic_media {class time_ranges;}
namespace html::elements {class html_media_element;}
namespace html::elements {class html_video_element;}


namespace html::detail
{
    auto poster_frame(
            elements::html_video_element* element)
            -> auto; // TODO : return type

    auto media_element_load_algorithm(
            elements::html_media_element* element)
            -> void;

    auto resource_selection_algorithm(
            elements::html_media_element* element)
            -> void;

    auto dedicated_media_source_failure_steps(
            ext::vector<ext::promise<>>& promises)
            -> void;

    auto verify_media_response(
            const fetch::detail::response_t& response,
            elements::html_media_element* resource,
            const ext::any& byte_range)
            -> ext::boolean;

    auto resource_fetch_algorithm(
            elements::html_media_element* element,
            const url::detail::url_t& url)
            -> void;

    auto media_data_processing_steps_list(
            elements::html_media_element* element)
            -> void;

    auto forget_media_element_media_resource_specific_tracks(
            elements::html_media_element* element)
            -> void;

    auto earliest_possible_position(
            elements::html_media_element* element)
            -> ext::number<double>;

    auto when_network_state_changes(
            elements::html_media_element* element,
            const ext::number<ushort>& previous_ready_state,
            const ext::number<ushort>& new_ready_state)
            -> void;

    auto when_current_playback_position_at_end(
            elements::html_media_element* element)
            -> void;

    auto is_blocked_media_element(
            elements::html_media_element* element)
            -> ext::boolean;

    auto is_potentially_playing(
            elements::html_media_element* element)
            -> ext::boolean;

    auto is_eligible_for_autoplay(
            elements::html_media_element* element)
            -> ext::boolean;

    auto is_allowed_to_play(
            elements::html_media_element* element)
            -> ext::boolean;

    auto has_ended_playback(
            elements::html_media_element* element)
            -> ext::boolean;

    auto has_stopped_due_to_errors(
            elements::html_media_element* element)
            -> ext::boolean;

    auto has_paused_for_use_interaction(
            elements::html_media_element* element)
            -> ext::boolean;

    auto has_paused_for_in_band_content(
            elements::html_media_element* element)
            -> ext::boolean;

    auto take_pending_play_promises(
            elements::html_media_element* element)
            -> ext::vector<ext::promise<>>;

    auto resolve_pending_play_promises(
            elements::html_media_element* element)
            -> void;

    auto reject_pending_play_promises(
            elements::html_media_element* element)
            -> void;

    auto notify_about_playing(
            elements::html_media_element* element)
            -> void;

    auto internal_play_steps(
            elements::html_media_element* element)
            -> void;

    auto internal_pause_steps(
            elements::html_media_element* element)
            -> void;

    auto direction_of_playback(
            elements::html_media_element* element)
            -> media_playback_direction_t;

    auto time_marches_on(
            elements::html_media_element* element)
            -> void;

    auto seek(
            elements::html_media_element* element,
            const ext::number<double>& new_playback_position,
            ext::boolean&& approximate_for_speed_flag)
            -> void;

    auto populate_pending_text_tracks(
            elements::html_media_element* element)
            -> void;

    auto media_element_text_tracks_ready(
            elements::html_media_element* element)
            -> void;

    auto when_text_track_mode_changes(
            elements::html_media_element* element,
            basic_media::text_track* text_track)
            -> void;

    auto is_unbounded_text_track_cue(
            basic_media::text_track_cue* text_track_cue)
            -> ext::boolean;

    auto is_media_resource_specific_text_track(
            basic_media::text_track* text_track)
            -> ext::boolean;

    auto expose_media_resource_specific_text_track(
            ext::any&& relevant_data)
            -> void;

    auto when_text_track_added_to_media_elements_text_tracks(
            elements::html_media_element* element,
            basic_media::text_track* text_track)
            -> void;

    auto honor_user_preferences_for_automatic_text_track_selection(
            elements::html_media_element* element)
            -> void;

    auto perform_automatic_text_track_selection(
            ext::vector<text_track_kind_t> text_track_kinds)
            -> void;

    auto start_track_processing_model(
            basic_media::text_track* text_track,
            html::elements::html_track_element* track_element)
            -> void;

    auto earliest_possible_position_when_script_started(
            /* TODO */)
            -> void;

    auto active_flag_was_set_when_script_started(
            /* TODO */)
            -> void;

    auto is_muted(
            elements::html_media_element* element)
            -> ext::boolean;

    auto effective_media_volume(
            elements::html_media_element* element)
            -> ext::number<double>;

    auto is_normalized_time_ranges(
            basic_media::time_ranges* time_range)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_MEDIA_INTERNALS_HPP
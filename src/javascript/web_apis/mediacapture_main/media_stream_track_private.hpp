#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_STREAM_TRACK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_STREAM_TRACK_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"
#include "mediacapture_main/mixins/constrainable_private.hpp"

#include INCLUDE_INNER_TYPES(mediacapture_handle)
#include INCLUDE_INNER_TYPES(mediacapture_main)


DEFINE_PRIVATE_CLASS(mediacapture::main, media_stream_track)
        : dom::nodes::event_target_private
        , mixins::constrainable_private
{
    ext::string kind;
    ext::string id;
    ext::string label;
    ext::boolean enabled;
    ext::boolean muted;
    detail::media_stream_track_state_t ready_state;

    std::unique_ptr<detail::media_stream_track_source> source;

    /* [MEDIACAPTURE-HANDLE] */
    ext::vector<detail::capture_action_t> available_capture_actions;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_MEDIA_STREAM_TRACK_PRIVATE_HPP

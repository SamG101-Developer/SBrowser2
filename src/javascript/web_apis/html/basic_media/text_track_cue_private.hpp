#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include "ext/boolean.hpp"
#include "ext/number.hpp"
#include "ext/vector.hpp"


DEFINE_PRIVATE_CLASS(html::basic_media, text_track_cue) : dom::nodes::event_target_private
{
    ext::string id;
    ext::number<double> start_time;
    ext::number<double> end_time;
    ext::boolean pause_on_exit_flag;

    ext::boolean active_flag;
    ext::vector<ext::number<int>> display_state;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_PRIVATE_HPP

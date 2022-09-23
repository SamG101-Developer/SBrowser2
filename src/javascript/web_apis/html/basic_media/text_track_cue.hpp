#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_HPP

#include "dom/nodes/event_target.hpp"
namespace html::basic_media {class text_track_cue;}

namespace html::basic_media {class text_track;}


class html::basic_media::text_track_cue
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(text_track_cue);
    text_track_cue() = default;

private js_properties:
    ext::property<ext::string> id;
    ext::property<ext::number<double>> start_time;
    ext::property<ext::number<double>> end_time;
    ext::property<ext::boolean> pause_on_exit;

    ext::property<text_track*> track;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean m_pause_on_exit_flag;
    ext::boolean m_active_flag;
    ext::vector<ext::number<int>> m_display_state;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_HPP


namespace html::basic_media {class text_track_cue;}
namespace html::basic_media {class text_track_cue_private;}

namespace html::basic_media {class text_track;}


class html::basic_media::text_track_cue
        : public dom::nodes::event_target
{
public constructors:
    DOM_CTORS(text_track_cue);
    MAKE_PIMPL(text_track_cue);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(id, ext::string_view);
    DEFINE_GETTER(start_time, ext::number<double>);
    DEFINE_GETTER(end_time, ext::number<double>);
    DEFINE_GETTER(pause_on_exit, ext::boolean);
    DEFINE_GETTER(track, text_track*);

    DEFINE_SETTER(id, ext::string);
    DEFINE_SETTER(start_time, ext::number<double>);
    DEFINE_SETTER(end_time, ext::number<double>);
    DEFINE_SETTER(pause_on_exit, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_CUE_HPP

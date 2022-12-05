#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_HPP


namespace html::basic_media {class abstract_track;}
namespace html::basic_media {class abstract_track_private;}

#include INCLUDE_INNER_TYPES(html)


class html::basic_media::abstract_track
        : public virtual dom_object
{
public constructors:
    abstract_track();
    MAKE_PIMPL(abstract_track);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(id, ext::string_view);
    DEFINE_GETTER(label, ext::string_view);
    DEFINE_GETTER(language, ext::string_view);
    DEFINE_GETTER(kind, html::detail::text_track_kind_t);

    /* [MEDIA-SOURCE] */
    DEFINE_GETTER(source_buffer, media::source::source_buffer*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_HPP

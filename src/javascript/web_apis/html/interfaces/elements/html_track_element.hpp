#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_track_element;}
namespace html::elements {class html_track_element_private;}

#include INCLUDE_INNER_TYPES(html)
namespace html::basic_media {class text_track;}


class html::elements::html_track_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_track_element);
    MAKE_PIMPL(html_track_element);
    MAKE_V8_AVAILABLE;

private js_static_constants:
    constexpr static const ext::number<ushort> NONE = 0;
    constexpr static const ext::number<ushort> LOADING = 1;
    constexpr static const ext::number<ushort> LOADED = 2;
    constexpr static const ext::number<ushort> ERROR = 3;

private js_properties:
    DEFINE_GETTER(kind, detail::track_element_kind_t);
    DEFINE_GETTER(src, ext::string_view);
    DEFINE_GETTER(srclang, ext::string_view);
    DEFINE_GETTER(label, ext::string_view);
    DEFINE_GETTER(default_, ext::boolean);
    DEFINE_GETTER(ready_state, ext::number<ushort>);
    DEFINE_GETTER(track, html::basic_media::text_track*);

    DEFINE_SETTER(kind, detail::track_element_kind_t);
    DEFINE_SETTER(src, ext::string);
    DEFINE_SETTER(srclang, ext::string);
    DEFINE_SETTER(label, ext::string);
    DEFINE_SETTER(default_, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_HPP

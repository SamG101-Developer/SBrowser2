#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_track_element;}

namespace html::basic_media {class text_track;}


class html::elements::html_track_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_track_element);
    html_track_element() = default;

public js_static_constants:
    constexpr static const ext::number<ushort> NONE = 0;
    constexpr static const ext::number<ushort> LOADING = 1;
    constexpr static const ext::number<ushort> LOADED = 2;
    constexpr static const ext::number<ushort> ERROR = 3;

public js_properties:
    ext::property<ext::string> kind;
    ext::property<ext::string> src;
    ext::property<ext::string> srclang;
    ext::property<ext::string> label;
    ext::property<ext::boolean> default_;
    ext::property<ext::number<ushort>> ready_state;
    ext::property<html::basic_media::text_track*> track;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_TRACK_ELEMENT_HPP

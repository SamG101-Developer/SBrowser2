#pragma once
#ifndef SBROWSER2_HTML_VIDEO_ELEMENT_HPP
#define SBROWSER2_HTML_VIDEO_ELEMENT_HPP

#include "html/elements/html_media_element.hpp"
namespace html::elements {class html_video_element;}


class html::elements::html_video_element
        : public html_media_element
{
public constructors:
    DOM_CTORS(html_video_element);
    html_video_element() = default;

public js_properties:
    ext::property<ext::number<ulong>> width;
    ext::property<ext::number<ulong>> height;
    ext::property<ext::number<ulong>> video_width;
    ext::property<ext::number<ulong>> video_height;
    ext::property<ext::string> poster;
    ext::property<ext::boolean> plays_inline;

private cpp_accessors:
    DEFINE_GETTER(video_width);
    DEFINE_GETTER(video_height);
};


#endif //SBROWSER2_HTML_VIDEO_ELEMENT_HPP

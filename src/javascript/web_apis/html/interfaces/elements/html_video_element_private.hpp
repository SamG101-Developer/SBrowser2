#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_VIDEO_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_VIDEO_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_media_element_private.hpp"

#include INCLUDE_INNER_TYPES(url)


DEFINE_PRIVATE_CLASS(html::elements, html_video_element) : html::elements::html_media_element_private
{
    std::unique_ptr<url::detail::url_t> poster;
    ext::boolean plays_inline;

    /* [MEDIA-PLAYBACK-QUALITY] */
    ext::number<int> total_video_frame_count   = 0;
    ext::number<int> dropped_video_frame_count = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_VIDEO_ELEMENT_PRIVATE_HPP

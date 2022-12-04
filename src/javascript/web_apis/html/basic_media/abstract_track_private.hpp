#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(html)

namespace media::source {class source_buffer;}


DEFINE_PRIVATE_CLASS(html::basic_media, abstract_track) : virtual dom_object_private
{
    ext::string id;
    ext::string label;
    ext::string language;
    detail::text_track_kind_t kind;

    /* [MEDIA-SOURCE] */
    std::unique_ptr<media::source::source_buffer> source_buffer;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_PRIVATE_HPP

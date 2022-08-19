#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP

#include "dom_object.hpp"
namespace html::basic_media {class text_track;}

namespace media::source {class source_buffer;}


class html::basic_media::text_track
        : public dom_object
{
public js_properties:
    ext::property<std::unique_ptr<media::source::source_buffer>> source_buffer;

private cpp_accessors:
    DEFINE_GETTER(source_buffer);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_HPP

module;
#include "ext/macros/pimpl.hpp"


export module apis.html.abstract_track_private;
import apis.dom_object_private;
import apis.html.types;

import ext.string;

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

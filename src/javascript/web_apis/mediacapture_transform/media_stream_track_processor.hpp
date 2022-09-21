#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_MEDIA_STREAM_TRACK_PROCESSOR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_MEDIA_STREAM_TRACK_PROCESSOR_HPP

#include "dom_object.hpp"
namespace mediacapture::transform {class media_stream_track_processor;}

#include "ext/queue.hpp"
#include INCLUDE_INNER_TYPES(mediacapture_transform)
namespace streams::readable {class readable_stream;}
namespace mediacapture::main {class media_stream_track;}


class mediacapture::transform::media_stream_track_processor
        : public dom_object
{
public constructors:
    media_stream_track_processor() = default;
    media_stream_track_processor(detail::media_stream_track_processor_init_t&& init);

public js_properties:
    ext::property<std::unique_ptr<streams::readable::readable_stream>> readable;

private js_slots:
    ext::slot<std::unique_ptr<main::media_stream_track>> s_track;
    ext::slot<ext::number<ushort>> s_max_buffer_size;
    ext::slot<ext::queue<ext::string>> s_queue; // TODO: queue<T> -> T?
    ext::slot<ext::number<int>> s_num_pending_reads;
    ext::slot<ext::boolean> s_is_closed;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_SETTER(s_track);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_TRANSFORM_MEDIA_STREAM_TRACK_PROCESSOR_HPP

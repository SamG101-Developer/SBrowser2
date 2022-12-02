#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP

#include "dom/nodes/event_target.hpp"
namespace media::source {class media_source;}
namespace media::source {class media_source_private;}

#include INCLUDE_INNER_TYPES(media_source)
#include "ext/optional.hpp"
#include "ext/number.ixx"
#include "ext/ranges.hpp"
namespace html::basic_media {class time_ranges;}
namespace html::messaging {class message_port;}
namespace media::source {class media_source_handle;}
namespace media::source {class source_buffer;}


class media::source::media_source
        : public dom::nodes::event_target
{
public constructors:
    media_source();
    MAKE_PIMPL(media_source);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto add_source_buffer(ext::string_view type) -> source_buffer*;
    auto remove_source_buffer(source_buffer* buffer) -> void;
    auto end_of_stream(ext::optional<detail::end_of_stream_error_t> error) -> void;
    auto set_live_seekable_range(ext::number<double> start, ext::number<double> end) -> void;
    auto clear_live_seekable_range() -> void;
    static auto is_type_supported(ext::string_view type) -> ext::boolean;

private js_properties:
    DEFINE_GETTER(handle, media_source_handle*);
    DEFINE_GETTER(source_buffers, ranges::any_helpful_view<source_buffer*>);
    DEFINE_GETTER(active_source_buffers, ranges::any_helpful_view<source_buffer*>);
    DEFINE_GETTER(ready_state, detail::ready_state_t);
    DEFINE_GETTER(duration, ext::number<double>);
    DEFINE_STATIC_GETTER(can_construct_in_dedicated_worker, ext::boolean);

    DEFINE_SETTER(duration, ext::number<double>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP

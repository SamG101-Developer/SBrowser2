#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP

#include "dom/nodes/event_target.hpp"
namespace media::source {class media_source;}

#include "ext/optional.hpp"
#include "ext/number.hpp"
#include "ext/slot.hpp"
#include INCLUDE_INNER_TYPES(media_source)
namespace html::basic_media {class time_ranges;}
namespace html::messaging {class message_port;}
namespace media::source {class media_source_handle;}
namespace media::source {class source_buffer;}


class media::source::media_source
        : public dom::nodes::event_target
{
public constructors:
    media_source();

public js_methods:
    auto add_source_buffer(const ext::string& type) -> source_buffer;
    auto remove_source_buffer(source_buffer* source_buffer) -> void;
    auto end_of_stream(ext::optional<detail::end_of_stream_error_t> error) -> void;
    auto set_live_seekable_range(ext::number<double> start, ext::number<double> end) -> void;
    auto clear_live_seekable_range() -> void;
    static auto is_type_supported(ext::string_view type) -> ext::boolean;


private js_properties:
    ext::property<std::unique_ptr<media_source_handle>> handle;
    ext::property<ext::vector<source_buffer*>> source_buffers;
    ext::property<ext::vector<source_buffer*>> active_source_buffers;
    ext::property<detail::ready_state_t> ready_state;
    ext::property<ext::number<double>> duration;
    static ext::property<ext::boolean> can_construct_in_dedicated_worker;

private js_slots:
    ext::slot<std::unique_ptr<html::basic_media::time_ranges>> s_live_seekable_range;
    ext::slot<std::unique_ptr<html::messaging::message_port>> s_port_to_main;

private js_properties:
    DEFINE_CUSTOM_GETTER(handle);
    DEFINE_CUSTOM_GETTER(duration);

    DEFINE_CUSTOM_SETTER(duration);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP

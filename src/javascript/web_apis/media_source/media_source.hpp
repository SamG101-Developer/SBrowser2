#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP

#include "dom/nodes/event_target.hpp"
namespace media::source {class media_source;}

#include "ext/optional.hpp"
#include "ext/number.hpp"
#include USE_INNER_TYPES(media_source)
namespace media::source {class media_source_handle;}
namespace media::source {class source_buffer;}

class media::source::media_source
        : public dom::nodes::event_target
{
public constructors:
    media_source();

public js_properties:
    ext::property<std::unique_ptr<media_source_handle>> handle;
    ext::property<ext::vector<source_buffer*>> source_buffers;
    ext::property<ext::vector<source_buffer*>> active_source_buffers;
    ext::property<detail::ready_state_t> ready_state;
    ext::property<ext::number<double>> duration;
    ext::property<ext::boolean> can_construct_in_dedicated_worker;

public js_methods:
    auto add_source_buffer(const ext::string& type) -> source_buffer;
    auto remove_source_buffer(source_buffer* source_buffer) -> void;
    auto end_of_stream(ext::optional<detail::end_or_stream_error> error) -> void;
    auto set_live_seekable_range(ext::number<double> start, ext::number<double> end) -> void;
    static auto is_type_supported(ext::string_view type) -> ext::boolean;

private js_slots:
    // TODO : [[live_seekable_range]]

private cpp_accessors:
    DEFINE_GETTER(duration)
    DEFINE_SETTER(duration)
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HPP

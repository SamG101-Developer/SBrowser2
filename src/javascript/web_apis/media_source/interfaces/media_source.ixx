module;
#include "ext/macros.hpp"
#include <tl/optional.hpp>


export module apis.media_source.media_source;
import apis.dom.event_target;
import apis.media_source.types;


DEFINE_PUBLIC_CLASS(media_source, media_source) final
        : public dom::event_target
{
public constructors:
    media_source();
    MAKE_PIMPL(media_source);
    MAKE_V8_AVAILABLE(WINDOW | DEDICATED_WORKER);

private js_methods:
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

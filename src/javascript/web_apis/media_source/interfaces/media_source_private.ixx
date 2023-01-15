module;
#include "ext/macros.hpp"


export module apis.media_source.media_source:p;
import apis.dom.event_target;
import apis.media_source.types;


DEFINE_PRIVATE_CLASS(media_source, media_source) : dom::event_target_private
{
public:
    MAKE_QIMPL(media_source);

public:
    std::unique_ptr<media_source_handle> handle;
    ext::vector<std::unique_ptr<source_buffer>> source_buffers;
    ranges::any_helpful_view<source_buffer*> active_source_buffers = source_buffers | ranges::views::transform(&std::unique_ptr<source_buffer>::get); // TODO : filter
    detail::ready_state_t ready_state;
    ext::number<double> duration;

    std::unique_ptr<html::time_ranges> live_seekable_range;
    std::unique_ptr<html::message_port> port_to_main;
};

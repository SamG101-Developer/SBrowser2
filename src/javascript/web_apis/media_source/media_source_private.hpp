#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(media_source)
#include "ext/ranges.hpp"
namespace media::source {class source_buffer;}
namespace media::source {class media_source_handle;}


DEFINE_PRIVATE_CLASS(media::source, media_source) : dom::nodes::event_target_private
{
    std::unique_ptr<media_source_handle> handle;
    ext::vector<std::unique_ptr<source_buffer>> source_buffers;
    ranges::any_helpful_view<source_buffer*> active_source_buffers = source_buffers | ranges::views::transform(&std::unique_ptr<source_buffer>::get); // TODO : filter
    detail::ready_state_t ready_state;
    ext::number<double> duration;

    std::unique_ptr<html::basic_media::time_ranges> live_seekable_range;
    std::unique_ptr<html::messaging::message_port> port_to_main;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_PRIVATE_HPP

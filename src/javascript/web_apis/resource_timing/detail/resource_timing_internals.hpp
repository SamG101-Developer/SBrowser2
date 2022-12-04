#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_DETAIL_RESOURCE_TIMING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_DETAIL_RESOURCE_TIMING_INTERNALS_HPP


#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(hr_time)
#include INCLUDE_INNER_TYPES(performance_timeline)
#include INCLUDE_INNER_TYPES(resource_timing)
namespace resource_timing {class performance_resource_timing;}

namespace resource_timing::detail
{
    auto can_add_resource_timing_entry()
            -> ext::boolean;

    auto add_performance_resource_timing_entry(
            performance_timeline::detail::performance_entry_buffer_map_t& buffer)
            -> void;

    auto copy_secondary_buffer()
            -> void;

    auto fire_buffer_full_event()
            -> void;

    auto mark_resource_timing(
            fetch::detail::fetch_timing_info_t& timing_info,
            ext::string_view requested_url,
            ext::string_view initiator_type,
            v8::Local<v8::Object> global_object,
            ext::string_view cache_mode,
            fetch::detail::response_body_info_t& body_info)
            -> void;

    auto setup_resource_timing_entry(
            performance_resource_timing* entry,
            fetch::detail::initiator_type_t initiator_type,
            ext::string_view requested_url,
            fetch::detail::fetch_timing_info_t&& fetch_timing,
            cache_mode_t cache_mode,
            fetch::detail::response_body_info_t&& body_info)
            -> void;

    auto convert_fetch_timestamp(
            const hr_time::dom_high_res_time_stamp& time_stamp,
            v8::Local<v8::Object> global)
            -> hr_time::dom_high_res_time_stamp;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_DETAIL_RESOURCE_TIMING_INTERNALS_HPP

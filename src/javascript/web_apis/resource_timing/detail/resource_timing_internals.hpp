#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_DETAIL_RESOURCE_TIMING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_DETAIL_RESOURCE_TIMING_INTERNALS_HPP

#include "ext/boolean.hpp"
#include USE_INNER_TYPES(fetch)
#include USE_INNER_TYPES(high_resolution_time)
#include USE_INNER_TYPES(performance_timeline)
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
            ext::string_view initiator_tpye,
            ext::string_view requested_url,
            ext::string_view cache_mode,
            fetch::detail::response_body_info_t& body_info)
            -> void;

    auto convert_fetch_timestamp(
            const high_resolution_time::detail::dom_high_res_time_stamp_t& time_stamp,
            v8::Local<v8::Object> global)
            -> high_resolution_time::detail::dom_high_res_time_stamp_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_RESOURCE_TIMING_DETAIL_RESOURCE_TIMING_INTERNALS_HPP

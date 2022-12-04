#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_DETAIL_PROCESSING_INTERNALS_HPP


#include "ext/string.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(performance_timeline)
namespace performance_timeline {class performance_entry;}


namespace performance_timeline::detail
{
    auto queue_performance_entry(
            performance_entry* new_entry)
            -> void;

    auto queue_performance_observer_task(
            v8::Local<v8::Object> relevant_global_object)
            -> void;

    auto filter_buffer_map_by_name_and_type(
            ext::string_view name = "",
            ext::string_view type = "")
            -> void;

    auto filter_buffer_by_name_and_type(
            v8::Local<v8::ArrayBuffer> buffer,
            ext::string_view name = "",
            ext::string_view type = "")
            -> void;

    auto determine_if_performance_entry_buffer_is_full(
            detail::performance_entry_buffer_map_tuple_t& tuple)
            -> ext::boolean;
};


struct performance_timeline::detail::performance_entry_buffer_map_tuple_t
{
    performance_entry_list_t performance_entry_buffer;
    ext::number<int> max_buffer_size;
    ext::number<int> dropped_entries_count = 0;
    ext::boolean available_from_timeline;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_DETAIL_PROCESSING_INTERNALS_HPP

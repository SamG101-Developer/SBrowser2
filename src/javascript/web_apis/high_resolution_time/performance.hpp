#pragma once
#ifndef SBROWSER2_PERFORMANCE_HPP
#define SBROWSER2_PERFORMANCE_HPP

#include "dom/nodes/event_target.hpp"
namespace high_resolution_time {class performance;}

#include USE_INNER_TYPES(high_resolution_time)
namespace performance_timeline {class performance_entry;}


class high_resolution_time::performance
        : public dom::nodes::event_target
{
public constructors:
    performance();

public js_methods:
    auto now() -> detail::dom_high_res_time_stamp_t;

    /* PERFORMANCE_TIMELINE */
    auto get_entries() -> ext::vector<performance_timeline::performance_entry*>;
    auto get_entries_by_type(ext::string_view type) -> ext::vector<performance_timeline::performance_entry*>;
    auto get_entries_by_name(ext::string_view name, ext::string_view type = "") -> ext::vector<performance_timeline::performance_entry*>;

public js_properties:
    ext::property<detail::dom_high_res_time_stamp_t> time_origin;

public cpp_properties:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_time_origin() const -> detail::dom_high_res_time_stamp_t;
};


// TODO : `ext::property<Performance> performance` in `WindowOrWorkerGlobalScope`


#endif //SBROWSER2_PERFORMANCE_HPP

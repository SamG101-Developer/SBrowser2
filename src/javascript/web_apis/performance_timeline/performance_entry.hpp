#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP

#include "dom_object.hpp"
namespace performance_timeline {class performance_entry;}

#include USE_INNER_TYPES(high_resolution_time)


class performance_timeline::performance_entry
        : public dom_object
{
public constructors:
    DOM_CTORS(performance_entry);
    performance_entry() = default;

public js_properties:
    ext::property<ext::string> name;
    ext::property<ext::string> entry_type;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> start_type;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> duration;

public cpp_methods:
    auto to_json() const -> ext::string override;
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP

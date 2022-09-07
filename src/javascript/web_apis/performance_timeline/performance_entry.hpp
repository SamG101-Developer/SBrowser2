#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP

#include "dom_object.hpp"
namespace performance_timeline {class performance_entry;}

#include USE_INNER_TYPES(hr_time)


class performance_timeline::performance_entry
        : public dom_object
{
public constructors:
    performance_entry() = default;

public js_properties:
    ext::property<ext::string> name;
    ext::property<ext::string> entry_type;
    ext::property<hr_time::dom_high_res_time_stamp> start_time;
    ext::property<hr_time::dom_high_res_time_stamp> duration;

public cpp_methods:
    auto to_json() const -> ext::string override;
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

protected cpp_accessors:
    virtual DEFINE_GETTER(name) = 0;
    virtual DEFINE_GETTER(entry_type) = 0;
    virtual DEFINE_GETTER(start_time) = 0;
    virtual DEFINE_GETTER(duration) = 0;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PERFORMANCE_TIMELINE_PERFORMANCE_ENTRY_HPP

#include "dom_point.hpp"

#include "css/geometry/dom_point_readonly.hpp"


auto css::geometry::dom_point::from_point(
        detail::dom_point_init_t&& other)
        -> dom_point
{
    // Create a DomPoint object from the dictionary of object passed into the method.
    return dom_point
    {
        other.try_emplace("x").first->second.to<ext::number<long>>(),
        other.try_emplace("y").first->second.to<ext::number<long>>(),
        other.try_emplace("z").first->second.to<ext::number<long>>(),
        other.try_emplace("w").first->second.to<ext::number<long>>()
    };
}


auto css::geometry::dom_point::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<dom_point>{isolate}
        .ctor<ext::number<double>, ext::number<double>, ext::number<double>, ext::number<double>>()
        .inherit<dom_point_readonly>()
        .function("fromPoint", &dom_point_readonly::from_point)
        .var("x", &dom_point_readonly::x, false)
        .var("x", &dom_point_readonly::y, false)
        .var("x", &dom_point_readonly::z, false)
        .var("x", &dom_point_readonly::w, false)
        .auto_wrap_objects();
}

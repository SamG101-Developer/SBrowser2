#include "dom_point_readonly.hpp"

#include "ext/number.ixx"

#include "css/geometry/dom_matrix.hpp"
#include "css/geometry/dom_point.hpp"
#include "css/geometry/detail/transformation_internals.hpp"


css::geometry::dom_point_readonly::dom_point_readonly(
        ext::number<double> x,
        ext::number<double> y,
        ext::number<double> z,
        ext::number<double> w)

        : x{x}, y{y}, z{z}, w{w}
{
}


auto css::geometry::dom_point_readonly::from_point(
        detail::dom_point_init_t&& other)
        -> dom_point_readonly
{
    // Create a DomPointReadonly object from the dictionary of object passed into the method.
    return dom_point_readonly
    {
        other.try_emplace("x").first->second.to<ext::number<long>>(),
        other.try_emplace("y").first->second.to<ext::number<long>>(),
        other.try_emplace("z").first->second.to<ext::number<long>>(),
        other.try_emplace("w").first->second.to<ext::number<long>>()
    };
}


auto css::geometry::dom_point_readonly::matrix_transform(
        detail::dom_matrix_init_t&& matrix)
        -> dom_point
{
    auto matrix_object = dom_matrix::from_matrix(std::move(matrix));
    return detail::transform_point_with_matrix(this, &matrix_object);
}


auto css::geometry::dom_point_readonly::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<dom_point_readonly>{isolate}
        .ctor<ext::number<double>, ext::number<double>, ext::number<double>, ext::number<double>>()
        .inherit<dom_object>()
        .function("fromPoint", &dom_point_readonly::from_point)
        .function("matrixTransform", &dom_point_readonly::matrix_transform)
        .function("toJSON", &dom_point_readonly::operator ext::string)
        .var("x", &dom_point_readonly::x, true)
        .var("x", &dom_point_readonly::y, true)
        .var("x", &dom_point_readonly::z, true)
        .var("x", &dom_point_readonly::w, true)
        .auto_wrap_objects();

    return std::move(conversion);
}
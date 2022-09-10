#include "dom_point_readonly.hpp"

#include "ext/number.hpp"

#include "css/geometry/dom_point.hpp"

#include <Eigen/Dense>


css::geometry::dom_point_readonly::dom_point_readonly(
        const ext::number<double> x,
        const ext::number<double> y,
        const ext::number<double> z,
        const ext::number<double> w)

        : x{x}, y{y}, z{z}, w{w}
{}


auto css::geometry::dom_point_readonly::from_point(
        detail::dom_point_init_t&& other)
        -> dom_point_readonly
{
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
    auto point_vector = Eigen::Vector<float, 4>{*x(), *y(), *z(), *w()};
    auto multiplier_matrix = Eigen::Matrix<float, 4, 4>{};
    multiplier_matrix <<
        *matrix.try_emplace("m11", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m12", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m13", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m14", 0).first->second.to<ext::number<float>>(),

        *matrix.try_emplace("m21", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m22", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m23", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m24", 0).first->second.to<ext::number<float>>(),

        *matrix.try_emplace("m31", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m32", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m33", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m34", 0).first->second.to<ext::number<float>>(),

        *matrix.try_emplace("m41", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m42", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m43", 0).first->second.to<ext::number<float>>(),
        *matrix.try_emplace("m44", 0).first->second.to<ext::number<float>>();
}


auto css::geometry::dom_point_readonly::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<dom_point_readonly>{isolate}
        .ctor<const ext::number<double>&, const ext::number<double>&, const ext::number<double>&, const ext::number<double>&>()
        .inherit<dom_object>()
        .function("fromPoint", &dom_point_readonly::from_point)
        .function("matrixTransform", &dom_point_readonly::matrix_transform)
        .function("toJSON", &dom_point_readonly::to_json)
        .var("x", &dom_point_readonly::x, true)
        .var("x", &dom_point_readonly::y, true)
        .var("x", &dom_point_readonly::z, true)
        .var("x", &dom_point_readonly::w, true)
        .auto_wrap_objects();
}
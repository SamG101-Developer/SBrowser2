#include "orientation_sensor.hpp"
#include "orientation_sensor_private.hpp"

#include "ext/concepts.hpp"
#include "ext/keywords.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "css/geometry/dom_matrix.hpp"
#include "dom/detail/exception_internals.hpp"
#include "sensors/detail/sensor_internals.hpp"

#include <qmatrix4x4.h>


auto orientation_sensor::orientation_sensor::populate_matrix(
        ext::vector<ext::number<double>>& target_matrix)
        -> void
{
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&target_matrix] {return target_matrix.size() < 16;},
            "List-like matrix must have >= 16 elements in it");

    auto candidate_quaternion = sensors::detail::get_value_from_latest_reading(this, "quaternion");
    dom::detail::throw_v8_exception<NOT_READABLE_ERR>(
            [empty = !candidate_quaternion.has_value()] {return empty;},
            "Quaternion can not be null");

    auto [x, y, z, w] = (*candidate_quaternion).to<ext::vector<ext::number<double>>>();

    target_matrix[0] = 1 - (2 * std::pow(y, 2)) - (2 * std::pow(z, 2));
    target_matrix[1] = (2 * x * y) - (2 * z * w);
    target_matrix[2] = (2 * x * z) + (2 * y * w);
    target_matrix[3] = 0;

    target_matrix[4] = (2 * x * y) + (2 * z * w);
    target_matrix[5] = 1 - (2 * std::pow(x, 2)) - (2 * std::pow(z, 2));
    target_matrix[6] = (2 * y * z) - (2 * y * w);
    target_matrix[7] = 0;

    target_matrix[8] = (2 * x * z) - (2 * y * w);
    target_matrix[9] = (2 * y * z) + (2 * x * w);
    target_matrix[10] = 1 - (2 * std::pow(x, 2)) - (2 * std::pow(y, 2));
    target_matrix[11] = 0;

    target_matrix[12] = 0;
    target_matrix[13] = 0;
    target_matrix[14] = 0;
    target_matrix[15] = 1;
}


auto orientation_sensor::orientation_sensor::populate_matrix(
        css::geometry::dom_matrix* target_matrix)
        -> void
{
    using enum dom::detail::dom_exception_error_t;

    auto candidate_quaternion = sensors::detail::get_value_from_latest_reading(this, "quaternion");
    dom::detail::throw_v8_exception<NOT_READABLE_ERR>(
            [empty = !candidate_quaternion.has_value()] {return empty;},
            "Quaternion can not be null");

    auto [x, y, z, w] = (*candidate_quaternion).to<ext::vector<ext::number<double>>>();

    target_matrix->d_func()->matrix = QMatrix4x4
    {
        1 - (2 * std::pow(y, 2)) - (2 * std::pow(z, 2)),
        (2 * x * y) - (2 * z * w),
        (2 * x * z) + (2 * y * w),
        0,

        (2 * x * y) + (2 * z * w),
        1 - (2 * std::pow(x, 2)) - (2 * std::pow(z, 2)),
        (2 * y * z) - (2 * y * w),
        0,

        (2 * x * z) - (2 * y * w),
        (2 * y * z) + (2 * x * w),
        1 - (2 * std::pow(x, 2)) - (2 * std::pow(y, 2)),
        0,

        0, 0, 0, 1
    };
}


auto orientation_sensor::orientation_sensor::get_quaternion() const -> ext::vector_view<ext::number<double>>
{
    // Get the latest reading for the "x" value, default it to 0 if it doesn't exist, and then convert it from the
    // ext::any type to a double. Return the double.
    auto candidate_quaternion = sensors::detail::get_value_from_latest_reading(this, "quaternion");
    auto defaulted_quaternion = candidate_quaternion.value_or(sensors::detail::sensor_reading_t{});
    auto extracted_quaternion = defaulted_quaternion.at("quaternion").to<ext::vector<ext::number<double>>>();
    return extracted_quaternion;
}

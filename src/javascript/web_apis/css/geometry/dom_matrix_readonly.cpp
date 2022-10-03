#include "dom_matrix_readonly.hpp"
#include "dom_matrix_readonly_private.hpp"

#include "css/geometry/dom_matrix.hpp"
#include "detail/transformation_internals.hpp"


auto css::geometry::dom_matrix_readonly::translate(
        ext::number<double> tx,
        ext::number<double> ty,
        ext::number<double> tz)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.translate_self(tx, ty, tz);
}


auto css::geometry::dom_matrix_readonly::scale(
        ext::number<double> sx, ext::number<double> sy, ext::number<double> sz,
        ext::number<double> ox, ext::number<double> oy, ext::number<double> oz)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.scale(sx, sy, sz, ox, oy, oz);
}


auto css::geometry::dom_matrix_readonly::scale_non_uniform(
        ext::number<double> sx, ext::number<double> sy)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.scale(sx, sy, 1, 0, 0, 0);
}


auto css::geometry::dom_matrix_readonly::scale3d(
        ext::number<double> s,
        ext::number<double> ox, ext::number<double> oy, ext::number<double> oz)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.scale3d_self(s, ox, oy, oz);
}


auto css::geometry::dom_matrix_readonly::rotate(
        ext::number<double> rx, ext::number<double> ry, ext::number<double> rz)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.rotate_self(rx, ry, rz);
}


auto css::geometry::dom_matrix_readonly::rotate_from_vector(
        ext::number<double> x, ext::number<double> y)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.rotate_from_vector_self(x, y);
}


auto css::geometry::dom_matrix_readonly::rotate_axis_angle(
        ext::number<double> x, ext::number<double> y, ext::number<double> z,
        ext::number<double> angle)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.rotate_axis_angle_self(x, y, z, angle);
}


auto css::geometry::dom_matrix_readonly::skew_x(
        ext::number<double> sx)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.skew_x_self(sx);
}


auto css::geometry::dom_matrix_readonly::skew_y(
        ext::number<double> sy)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.skew_y_self(sy);
}


auto css::geometry::dom_matrix_readonly::multiply(
        detail::dom_matrix_init_t&& other)
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.multiply_self(std::move(other));
}


auto css::geometry::dom_matrix_readonly::inverse()
        const -> dom_matrix
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return dom_matrix{d->matrix}.invert_self();
}


auto css::geometry::dom_matrix_readonly::flip_x()
        const -> dom_matrix
{
    auto other = dom_matrix::from_float32_array({
        ext::number<float>{-1.0}, ext::number<float>{0.0}, ext::number<float>{0.0}, ext::number<float>{1.0},
        ext::number<float>{0.0}, ext::number<float>{0.0}});

    return detail::post_multiply(this, std::move(other));
}


auto css::geometry::dom_matrix_readonly::flip_y()
        const -> dom_matrix
{
    auto other = dom_matrix::from_float32_array({
        ext::number<float>{1.0}, ext::number<float>{0.0}, ext::number<float>{0.0}, ext::number<float>{-1.0},
        ext::number<float>{0.0}, ext::number<float>{0.0}});

    return detail::post_multiply(this, std::move(other));
}


auto css::geometry::dom_matrix_readonly::get_a() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return d->matrix(0, 0);
}


auto css::geometry::dom_matrix_readonly::get_b() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return d->matrix(0, 1);
}


auto css::geometry::dom_matrix_readonly::get_c() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return d->matrix(1, 0);
}


auto css::geometry::dom_matrix_readonly::get_d() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return d->matrix(1, 1);
}


auto css::geometry::dom_matrix_readonly::get_e() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return d->matrix(3, 0);
}


auto css::geometry::dom_matrix_readonly::get_f() const -> ext::number<double>
{
    ACCESS_PIMPL(const dom_matrix_readonly);
    return d->matrix(3, 1);
}

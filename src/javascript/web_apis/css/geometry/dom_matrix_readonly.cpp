#include "dom_matrix_readonly.hpp"

#include "css/geometry/dom_matrix.hpp"
#include "detail/transformation_internals.hpp"


auto css::geometry::dom_matrix_readonly::translate(
        ext::number<double> tx,
        ext::number<double> ty,
        ext::number<double> tz)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.translate_self(tx, ty, tz);
}


auto css::geometry::dom_matrix_readonly::scale(
        ext::number<double> sx,
        ext::number<double> sy,
        ext::number<double> sz,
        ext::number<double> ox,
        ext::number<double> oy,
        ext::number<double> oz)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.scale(sx, sy, sz, ox, oy, oz);
}


auto css::geometry::dom_matrix_readonly::scale_non_uniform(
        ext::number<double> sx,
        ext::number<double> sy)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.scale(sx, sy, 1, 0, 0, 0);
}


auto css::geometry::dom_matrix_readonly::scale3d(
        ext::number<double> s,
        ext::number<double> ox,
        ext::number<double> oy,
        ext::number<double> oz)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.scale3d_self(s, ox, oy, oz);
}


auto css::geometry::dom_matrix_readonly::rotate(
        ext::number<double> rx,
        ext::number<double> ry,
        ext::number<double> rz)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.rotate_self(rx, ry, rz);
}


auto css::geometry::dom_matrix_readonly::rotate_from_vector(
        ext::number<double> x,
        ext::number<double> y)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.rotate_from_vector_self(x, y);
}


auto css::geometry::dom_matrix_readonly::rotate_axis_angle(
        ext::number<double> x,
        ext::number<double> y,
        ext::number<double> z,
        ext::number<double> angle)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.rotate_axis_angle_self(x, y, z, angle);
}


auto css::geometry::dom_matrix_readonly::skew_x(
        ext::number<double> sx)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.skew_x_self(sx);
}


auto css::geometry::dom_matrix_readonly::skew_y(
        ext::number<double> sy)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.skew_y_self(sy);
}


auto css::geometry::dom_matrix_readonly::multiply(
        detail::dom_matrix_init_t&& other)
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.multiply_self(std::move(other));
}


auto css::geometry::dom_matrix_readonly::inverse()
        const -> dom_matrix
{
    return dom_matrix{*d_ptr}.invert_self();
}


auto css::geometry::dom_matrix_readonly::flip_x()
        const -> dom_matrix
{
    return detail::post_multiply(
            *d_ptr,
            dom_matrix::from_float32_array(
            {
                ext::number<float>{-1.0},
                ext::number<float>{0.0},
                ext::number<float>{0.0},
                ext::number<float>{1.0},
                ext::number<float>{0.0},
                ext::number<float>{0.0}
            }));
}


auto css::geometry::dom_matrix_readonly::flip_y()
        const -> dom_matrix
{
    return detail::post_multiply(
            *d_ptr,
            dom_matrix::from_float32_array(
            {
                    ext::number<float>{1.0},
                    ext::number<float>{0.0},
                    ext::number<float>{0.0},
                    ext::number<float>{-1.0},
                    ext::number<float>{0.0},
                    ext::number<float>{0.0}
            }));
}

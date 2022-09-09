#include "canvas_transform.hpp"

#include "ext/number.hpp"

#include <QtGui/QMatrix3x3>


auto html::canvasing::mixins::canvas_transform::scale(
        const ext::number<double>& x,
        const ext::number<double>& y)
        -> void
{
    return_if (ext::is_inf_or_nan(x, y));
    m_current_transform_matrix.scale(std::bit_cast<qreal>(*x), std::bit_cast<qreal>(*y));
}


auto html::canvasing::mixins::canvas_transform::rotate(
        const ext::number<double>& angle)
        -> void
{
    return_if (ext::is_inf_or_nan(angle));
    m_current_transform_matrix.rotate(std::bit_cast<qreal>(*angle));
}


auto html::canvasing::mixins::canvas_transform::translate(
        const ext::number<double>& x,
        const ext::number<double>& y)
        -> void
{
    return_if (ext::is_inf_or_nan(x, y));
    m_current_transform_matrix.translate(std::bit_cast<qreal>(*x), std::bit_cast<qreal>(*y));
}


auto html::canvasing::mixins::canvas_transform::transform(
        const ext::number<double>& a,
        const ext::number<double>& b,
        const ext::number<double>& c,
        const ext::number<double>& d,
        const ext::number<double>& e,
        const ext::number<double>& f)
        -> void
{
    return (ext::is_inf_or_nan(a, b, c, d, e, f));

    decltype(auto) m = m_current_transform_matrix;

    auto lhs_matrix_values = {m.m11(), m.m12(), m.m13(), m.m21(), m.m22(), m.m23(), m.m31(), m.m32(), m.m33()};
    auto rhs_matrix_values = {*a, *c, *e, *b, *d, *f, 0.0, 0.0, 1.0};
    auto lhs_matrix = QMatrix3x3{std::bit_cast<float*>(lhs_matrix_values.begin())};
    auto rhs_matrix = QMatrix3x3{std::bit_cast<float*>(rhs_matrix_values.begin())};

    auto mult_matrix = lhs_matrix * rhs_matrix;
    m_current_transform_matrix.setMatrix()
}

#include "canvas_transform.hpp"

#include "ext/number.hpp"

#include <QtGui/QTransform>


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
    return_if (ext::is_inf_or_nan(a, b, c, d, e, f));

    auto other_matrix = ext::make_from_tuple<QTransform>(ext::tuple{*a, *c, *e, *b, *d, *f, 0.0, 0.0, 1.0});
    m_current_transform_matrix *= std::move(other_matrix);
}


auto html::canvasing::mixins::canvas_transform::get_transform()
        -> css::geometry::dom_matrix
{

}

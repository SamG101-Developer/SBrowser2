#include "canvas_transform.hpp"



#include "css/geometry/dom_matrix.hpp"
#include "css/geometry/dom_matrix_readonly.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/map.hpp>


auto html::canvasing::mixins::canvas_transform::scale(
        ext::number<double> x,
        ext::number<double> y)
        -> void
{
    return_if (ext::is_inf_or_nan(x, y));
    m_current_transform_matrix->scale(*x, *y);
}


auto html::canvasing::mixins::canvas_transform::rotate(
        ext::number<double> angle)
        -> void
{
    return_if (ext::is_inf_or_nan(angle));
    m_current_transform_matrix->rotate(*angle);
}


auto html::canvasing::mixins::canvas_transform::translate(
        ext::number<double> x,
        ext::number<double> y)
        -> void
{
    return_if (ext::is_inf_or_nan(x, y));
    m_current_transform_matrix->translate(*x, *y);
}


auto html::canvasing::mixins::canvas_transform::transform(
        ext::number<double> a,
        ext::number<double> b,
        ext::number<double> c,
        ext::number<double> d,
        ext::number<double> e,
        ext::number<double> f)
        -> void
{
    return_if (ext::is_inf_or_nan(a, b, c, d, e, f));

    auto other_matrix_init = {a, c, e, b, d, f, ext::number{0.0}, ext::number{0.0}, ext::number{1.0}};
    auto other_matrix = css::geometry::dom_matrix_readonly{other_matrix_init};
    *m_current_transform_matrix *= std::move(other_matrix);
}


auto html::canvasing::mixins::canvas_transform::get_transform()
        -> css::geometry::dom_matrix*
{
    return m_current_transform_matrix.get();
}


auto html::canvasing::mixins::canvas_transform::set_transform(
        ext::number<double> a,
        ext::number<double> b,
        ext::number<double> c,
        ext::number<double> d,
        ext::number<double> e,
        ext::number<double> f)
        -> void
{
    return_if (ext::is_inf_or_nan(a, b, c, d, e, f));
    reset_transform();
    transform(a, b, c, d, e, f);
}


auto html::canvasing::mixins::canvas_transform::set_transform(
        css::detail::dom_matrix_init_t&& other)
        -> void
{
    return_if (ranges::any_of(other | ranges::views::values, &ext::is_inf_or_nan));
    *m_current_transform_matrix = css::geometry::dom_matrix::from_matrix(std::move(other));
}


auto html::canvasing::mixins::canvas_transform::reset_transform()
        -> void
{
    m_current_transform_matrix->m_matrix.setToIdentity();
}

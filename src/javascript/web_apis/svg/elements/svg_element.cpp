#include "svg_element.hpp"
#include "svg_element_private.hpp"

#include "ext/ranges.hpp"

#include "dom/detail/tree_internals.hpp"

#include <range/v3/view/take.hpp>


auto svg::elements::svg_element::get_class_name() const -> types::svg_animated_string*
{
    ACCESS_PIMPL(const svg_element);
    return d->class_.get();
}


auto svg::elements::svg_element::get_owner_svg_element() const -> svg_svg_element*
{
    return dom::detail::ancestors(this)
            | ranges::views::cast_all_to.CALL_TEMPLATE_LAMBDA<svg_svg_element*>()
            | ranges::views::take(1);
}

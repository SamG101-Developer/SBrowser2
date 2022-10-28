#include "html_legend_element.hpp"
#include "html_legend_element_private.hpp"

#include "html/elements/html_field_set_element.hpp"
#include "html/elements/html_field_set_element_private.hpp"


auto html::elements::html_legend_element::get_form() const -> html_form_element*
{
    ACCESS_PIMPL(const html_legend_element);
    decltype(auto) parent = dynamic_cast<html_field_set_element*>(d->parent_node);
    return parent ? parent->d_func()->form_owner.get() : nullptr;
}

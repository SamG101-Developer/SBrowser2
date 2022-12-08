#include "html_opt_group_element.hpp"
#include "html_opt_group_element_private.hpp"




auto html::elements::html_opt_group_element::get_disabled() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_opt_group_element);
        return d->disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_opt_group_element::get_label() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_opt_group_element);
        return d->label;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_opt_group_element::set_disabled(ext::boolean new_disabled) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_opt_group_element);
        return d->disabled = new_disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_opt_group_element::set_label(ext::string new_label) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_opt_group_element);
        return d->label = std::move(new_label);
    CE_REACTIONS_METHOD_EXE
}


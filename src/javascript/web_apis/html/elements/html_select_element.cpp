#include "html_select_element.hpp"
#include "html_select_element_private.hpp"

#include "dom/detail/customization_internals.hpp"

#include "html/elements/html_option_element.hpp"
#include "html/elements/html_option_element_private.hpp"


html::elements::html_select_element::html_select_element()
        : ext::vector_like_linked<detail::option_like_element_t>{options()}
{
    INIT_PIMPL(html_select_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_select_element::get_autocomplete() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_select_element);
        return d->autocomplete;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::get_name() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_select_element);
        return d->name;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::get_value() const -> ext::string
{
    ACCESS_PIMPL(const html_select_element);
    return ranges::front(d->list_of_options()
            | ranges::views::filter_eq(&html_option_element_private::selectedness, true, ext::get_pimpl)
            | ranges::views::transform_to_attr(&html_option_element_private::value, ext::get_pimpl)); // TODO : move ->value outside
}


auto html::elements::html_select_element::get_disabled() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_select_element);
        return d->disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::get_form() const -> html_form_element*
{
    ACCESS_PIMPL(const html_select_element);
    return d->form_owner.get();
}


auto html::elements::html_select_element::get_multiple() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_select_element);
        return d->multiple;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::get_required() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_select_element);
        return d->required;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::get_size() const -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_select_element);
        return d->size;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::get_type() const -> ext::string
{
    ACCESS_PIMPL(const html_select_element);
    return d->multiple ? u8"select-multiple" : u8"select-one"; // TODO : enum
}


auto html::elements::html_select_element::set_autocomplete(ext::string new_autocomplete) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_select_element);
        return d->autocomplete = std::move(new_autocomplete);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::set_name(ext::string new_name) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_select_element);
        return d->name = std::move(new_name);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::set_value(ext::string new_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_select_element);
        return ranges::front(d->list_of_options()
                | ranges::views::filter_eq(&html_option_element_private::selectedness, true, ext::get_pimpl)).d_func()->value
                = std::move(new_value);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::set_disabled(ext::boolean new_disabled) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_select_element);
        return d->disabled = new_disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::set_multiple(ext::boolean new_multiple) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_select_element);
        return d->multiple = new_multiple;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::set_required(ext::boolean new_required) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_select_element);
        return d->required = new_required;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_select_element::set_size(ext::number<ulong> new_size) -> ext::number<ulong>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_select_element);
        return d->size = new_size;
    CE_REACTIONS_METHOD_EXE
}

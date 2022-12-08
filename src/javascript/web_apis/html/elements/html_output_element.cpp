#include "html_output_element.hpp"
#include "html_output_element_private.hpp"






auto html::elements::html_output_element::get_html_for() const -> ext::string_view
{
    ACCESS_PIMPL(const html_output_element);
    return d->for_;
}


auto html::elements::html_output_element::get_form() const -> html_form_element*
{
    ACCESS_PIMPL(const html_output_element);
    return d->form.get();
}


auto html::elements::html_output_element::get_name() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_output_element);
        return d->name;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_output_element::get_type() const -> ext::string
{
    return u"output";
}


auto html::elements::html_output_element::get_default_value() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_output_element);
        return d->default_value_override.empty()
                ? dom::detail::descendant_text_content(this)
                : d->default_value_override;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_output_element::get_value() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        return dom::detail::descendant_text_content(this);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_output_element::set_name(ext::string new_name) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_output_element);
        return d->name = std::move(new_name);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_output_element::set_default_value(ext::string new_default_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_output_element);
        return d->default_value_override.empty()
                ? dom::detail::string_replace_all(std::move(new_default_value), this)
                : d->default_value_override = std::move(new_default_value);
    CE_REACTIONS_METHOD_EXE
}
#include "html_button_element.hpp"
#include "html_button_element_private.hpp"





#include "url/detail/url_internals.hpp"
#include INCLUDE_INNER_TYPES(html)


html::elements::html_button_element::html_button_element()
{
    INIT_PIMPL(html_button_element);
    ACCESS_PIMPL(html_button_element);

    d->activation_behaviour = [this, d](dom::events::event* event)
            {
        return_if (d->disabled);
        return_if (!d->form);
        return_if (!dom::detail::is_document_fully_active(d->node_document));

        switch (d->type)
        {
            case detail::button_state_t::SUBMIT:
                detail::submit(d->form.get(), this);

            case detail::button_state_t::RESET:
                detail::reset(d->form.get(), this);

            case detail::button_state_t::BUTTON:
            default:
                ;
        }
            };
}


auto html::elements::html_button_element::get_form() const -> html_form_element*
{
    ACCESS_PIMPL(const html_button_element);
    return d->form.get();
}


auto html::elements::html_button_element::get_disabled() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::get_form_action() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return !d->form_action.empty() ? d->form_action : url::detail::url_serializer(*d->node_document->d_func()->url);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::get_form_enctype() const -> detail::form_enctype_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->form_enctype;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::get_form_method() const -> detail::form_method_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->form_method;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::get_form_no_validate() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->form_no_validate;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::get_form_target() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->form_target;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::get_name() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->name;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::get_type() const -> detail::button_state_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->type;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::get_value() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}

auto html::elements::html_button_element::set_disabled(ext::boolean new_disabled) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->disabled = new_disabled;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::set_form_action(ext::string new_form_action) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->form_action = std::move(new_form_action);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::set_form_enctype(detail::form_enctype_t new_form_enctype) -> detail::form_enctype_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->form_enctype = new_form_enctype;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::set_form_method(detail::form_method_t new_form_method) -> detail::form_method_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->form_method = new_form_method;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::set_form_no_validate(ext::boolean new_form_novalidate) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->form_no_validate = new_form_novalidate;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::set_form_target(ext::string new_form_target) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->form_target = std::move(new_form_target);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::set_name(ext::string new_name) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->name = std::move(new_name);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::set_type(detail::button_state_t new_type) -> detail::button_state_t
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->type = new_type;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_button_element::set_value(ext::string new_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->value = new_value;
    CE_REACTIONS_METHOD_EXE
}

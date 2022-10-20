#include "html_button_element.hpp"
#include "html_button_element_private.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/nodes/node.hpp"
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



auto html::elements::html_button_element::get_disabled() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_button_element);
        return d->disabled;
    CE_REACTIONS_METHOD_EXE
}

auto html::elements::html_button_element::set_disabled(ext::boolean new_disabled) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_button_element);
        return d->disabled = new_disabled;
    CE_REACTIONS_METHOD_EXE
}

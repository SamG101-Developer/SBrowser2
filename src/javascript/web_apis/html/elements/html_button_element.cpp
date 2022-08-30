#include "html_button_element.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/nodes/node.hpp"
#include USE_INNER_TYPES(html)


html::elements::html_button_element::html_button_element()
{
    m_dom_behaviour.activation_behaviour =
            [this](dom::events::event* event)
            {
                return_if (disabled());
                return_if (!form());
                return_if (!dom::detail::is_document_fully_active(owner_document()));

                switch (type())
                {
                    case detail::button_state_t::SUBMIT:
                        detail::submit(form(), this);

                    case detail::button_state_t::RESET:
                        detail::reset(form(), this);

                    case detail::button_state_t::BUTTON:
                    default:
                        ;
                }
            };
}

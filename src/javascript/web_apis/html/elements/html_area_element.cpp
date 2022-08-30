#include "html_area_element.hpp"

#include "dom/events/event.hpp"

#include "html/detail/link_internals.hpp"


html::elements::html_area_element::html_area_element()
{
    m_dom_behaviour.activation_behaviour =
            [this](dom::events::event* event)
            {
                return_if (href().empty());
                !download().empty() || detail::user_has_preference_to_download_hyperlink()
                        ? detail::download_hyperlink(this, href())
                        : detail::follow_hyperlink(this, href());
            };

    HTML_CONSTRUCTOR
}

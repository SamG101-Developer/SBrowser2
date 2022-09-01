#include "html_or_svg_element.hpp"


html::mixins::html_or_svg_element::html_or_svg_element()
{
    m_dom_behaviour.insertion_steps =
            [this]
            {
                if (autofocus())
                {
                    // TODO
                }
            };
}

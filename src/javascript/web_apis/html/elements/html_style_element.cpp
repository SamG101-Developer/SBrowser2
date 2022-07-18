#include "html_style_element.hpp"


html::elements::html_style_element::html_style_element()
{
    bind_get(disabled);
    bind_set(disabled);

    HTML_CONSTRUCTOR
}

#include "html_select_element.hpp"


html::elements::html_select_element::html_select_element()
        : ext::vector_like_linked<detail::option_like_element_t>{options()}
{
    HTML_CONSTRUCTOR
}

#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_HR_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_HR_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_hr_element;}
namespace html::elements {class html_hr_element_private;}


class html::elements::html_hr_element
        : public html_element
{
public constructors:
    DOM_CTORS(html_hr_element);
    MAKE_PIMPL(html_hr_element);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_HR_ELEMENT_HPP

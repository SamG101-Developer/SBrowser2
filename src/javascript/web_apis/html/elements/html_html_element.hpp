#ifndef SBROWSER2_HTML_HTML_ELEMENT_HPP
#define SBROWSER2_HTML_HTML_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_html_element;}


class html::elements::html_html_element
        : public html::elements::html_element
{
public constructors:
    html_html_element();

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_HTML_HTML_ELEMENT_HPP

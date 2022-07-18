#ifndef SBROWSER2_HTML_BODY_ELEMENT_HPP
#define SBROWSER2_HTML_BODY_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_body_element;}


class html::elements::html_body_element
        : public html_element
{
public constructors:
    html_body_element();

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_HTML_BODY_ELEMENT_HPP

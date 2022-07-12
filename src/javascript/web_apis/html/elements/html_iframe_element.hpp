#pragma once
#ifndef SBROWSER2_HTML_IFRAME_ELEMENT_HPP
#define SBROWSER2_HTML_IFRAME_ELEMENT_HPP

#include "html/elements/html_element.hpp"
namespace html::elements {class html_iframe_element}


class html::elements::html_iframe_element
        : public html_element
{
public js_properties:
    ext::property<std::unique_ptr<permissions_policy::permissions_policy>> permissions_policy;
};


#endif //SBROWSER2_HTML_IFRAME_ELEMENT_HPP

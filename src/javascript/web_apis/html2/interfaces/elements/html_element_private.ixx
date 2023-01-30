module;
#include "ext/macros.hpp"


export module apis.html.html_element:p;
import apis.dom.element;


DEFINE_PRIVATE_CLASS(html, html_element)
        : dom::element_private
        , html::mixins::element_content_editable_private
        , html::mixins::html_or_svg_element_private
{
public:
    MAKE_QIMPL(html_element);

public:
    ext::string is;
    ext::string itemid;
    ext::string itemprop;
    ext::string itemref;
    ext::string itemscope;
    ext::string itemtype;
    ext::string style;
};

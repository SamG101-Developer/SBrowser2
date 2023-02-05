module;
#include "ext/macros.hpp"


export module apis.html.html_data_element;
import apis.html.html_element;


DEFINE_PUBLIC_CLASS(html, html_data_element) final
        : public html::html_element
{
public constructors:
    html_data_element();
    MAKE_PIMPL(html_data_element);
    MAKE_V8_AVAILABLE();

public:
    DEFINE_GETTER(value, ext::string)
    DEFINE_SETTER(value, ext::string)
};

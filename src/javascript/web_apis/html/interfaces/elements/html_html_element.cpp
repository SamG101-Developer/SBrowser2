#include "html_html_element.hpp"


html::elements::html_html_element::html_html_element()
{
    INIT_PIMPL(html_html_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_html_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_html_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .auto_wrap_objects();

    return std::move(conversion);
}

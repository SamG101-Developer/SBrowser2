#include "html_div_element.hpp"


html::elements::html_div_element::html_div_element()
{
    INIT_PIMPL(html_div_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_div_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_div_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .auto_wrap_objects();

    return std::move(conversion);
}


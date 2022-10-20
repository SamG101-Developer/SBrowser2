#include "html_br_element.hpp"
#include "html_br_element_private.hpp"


html::elements::html_br_element::html_br_element()
{
    INIT_PIMPL(html_br_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_br_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_br_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .auto_wrap_objects();

    return std::move(conversion);
}

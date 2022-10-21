#include "html_head_element.hpp"
#include "html_head_element_private.hpp"


html::elements::html_head_element::html_head_element()
{
    INIT_PIMPL(html_head_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_head_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_head_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .auto_wrap_objects();

    return std::move(conversion);
}

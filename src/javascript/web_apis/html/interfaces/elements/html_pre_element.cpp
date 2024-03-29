#include "html_pre_element.hpp"
#include "html_pre_element_private.hpp"


html::elements::html_pre_element::html_pre_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_pre_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_pre_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .auto_wrap_objects();

    return std::move(conversion);
}

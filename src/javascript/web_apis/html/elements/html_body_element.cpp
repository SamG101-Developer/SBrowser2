#include "html_body_element.hpp"


html::elements::html_body_element::html_body_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_body_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_body_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .auto_wrap_objects();
}
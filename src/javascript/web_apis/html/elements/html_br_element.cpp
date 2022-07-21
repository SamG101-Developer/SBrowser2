#include "html_br_element.hpp"


html::elements::html_br_element::html_br_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_br_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_br_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .auto_wrap_objects();
}

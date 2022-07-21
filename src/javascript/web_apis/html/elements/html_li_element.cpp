#include "html_li_element.hpp"


html::elements::html_li_element::html_li_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_li_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_li_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .var("value", &html_li_element::value, false)
            .auto_wrap_objects();
}


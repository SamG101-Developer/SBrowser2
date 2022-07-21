#include "html_data_element.hpp"


html::elements::html_data_element::html_data_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_data_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_data_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .var("value", &html_data_element::value, false)
            .auto_wrap_objects();
}


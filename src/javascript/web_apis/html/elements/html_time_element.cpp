#include "html_time_element.hpp"


html::elements::html_time_element::html_time_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_time_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_time_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .var("dateTime", &html_time_element::date_time, false)
            .auto_wrap_objects();
}

#include "html_mod_element.hpp"


html::elements::html_mod_element::html_mod_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_mod_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_mod_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .var("cite", &html_mod_element::cite, false)
            .var("dateTime", &html_mod_element::date_time, false)
            .auto_wrap_objects();
}

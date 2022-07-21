#include "html_olist_element.hpp"


html::elements::html_olist_element::html_olist_element()
        : start(1)
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_olist_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_olist_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .var("reversed", &html_olist_element::reversed, false)
            .var("start", &html_olist_element::start, false)
            .var("type", &html_olist_element::type, false)
            .auto_wrap_objects();
}

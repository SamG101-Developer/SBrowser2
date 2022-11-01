#include "html_time_element.hpp"
#include "html_time_element_private.hpp"


html::elements::html_time_element::html_time_element()
{
    INIT_PIMPL(html_time_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_time_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_time_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .property("dateTime", &html_time_element::get_date_time, &html_time_element::set_date_time)
        .auto_wrap_objects();

    return std::move(conversion);
}

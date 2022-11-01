#include "html_ulist_element.hpp"
#include "html_ulist_element_private.hpp"


html::elements::html_ulist_element::html_ulist_element()
{
    INIT_PIMPL(html_ulist_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_ulist_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_ulist_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .auto_wrap_objects();

    return std::move(conversion);
}

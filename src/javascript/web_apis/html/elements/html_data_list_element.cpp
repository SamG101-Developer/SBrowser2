#include "html_data_list_element.hpp"


html::elements::html_data_list_element::html_data_list_element()
{
    INIT_PIMPL(html_data_list_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_data_list_element::get_options() const -> ranges::any_helpful_view<html_element>
{}


auto html::elements::html_data_list_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_data_list_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .auto_wrap_objects();

    return std::move(conversion);
}

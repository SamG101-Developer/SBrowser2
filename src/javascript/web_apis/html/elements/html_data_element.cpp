#include "html_data_element.hpp"
#include "html_data_element_private.hpp"




html::elements::html_data_element::html_data_element()
{
    INIT_PIMPL(html_data_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_data_element::get_value() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_data_element);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_data_element::set_value(ext::string new_value) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_data_element);
        return d->value = std::move(new_value);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_data_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_data_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .property("value", &html_data_element::get_value, &html_data_element::set_value)
        .auto_wrap_objects();
}

#include "html_li_element.hpp"
#include "html_li_element_private.hpp"

#include "dom/detail/customization_internals.hpp"


html::elements::html_li_element::html_li_element()
{
    INIT_PIMPL(html_li_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_li_element::get_value() const -> ext::number<long>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_li_element);
        return d->value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_li_element::set_value(ext::number<long> new_value) -> ext::number<long>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_li_element);
        return d->value = new_value;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_li_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_li_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .property("value", &html_li_element::get_value, &html_li_element::set_value)
        .auto_wrap_objects();

    return std::move(conversion);
}


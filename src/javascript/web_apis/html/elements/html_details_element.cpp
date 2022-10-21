#include "html_details_element.hpp"
#include "html_details_element_private.hpp"

#include "dom/detail/customization_internals.hpp"


html::elements::html_details_element::html_details_element()
{
    INIT_PIMPL(html_details_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_details_element::get_open() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_details_element);
        return d->open;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_details_element::set_open(ext::boolean new_open) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_details_element);
        return d->open = new_open;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_details_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_details_element>{isolate}
        .inherit<html_element>()
        .ctor<>()
        .property("open", &html_details_element::get_open, &html_details_element::set_open)
        .auto_wrap_objects();

    return std::move(conversion);
}

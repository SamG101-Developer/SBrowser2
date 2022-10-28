#include "html_olist_element.hpp"
#include "html_olist_element_private.hpp"

#include "dom/detail/customization_internals.hpp"


html::elements::html_olist_element::html_olist_element()
{
    INIT_PIMPL(html_olist_element);

    ACCESS_PIMPL(html_olist_element);
    d->start =1;

    HTML_CONSTRUCTOR
}


auto html::elements::html_olist_element::get_reversed() const -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_olist_element);
        return d->reversed;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_olist_element::get_start() const -> ext::number<long>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_olist_element);
        return d->start;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_olist_element::get_type() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_olist_element);
        return d->type;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_olist_element::set_reversed(ext::boolean new_reversed) -> ext::boolean
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_olist_element);
        return d->reversed = new_reversed;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_olist_element::set_start(ext::number<long> new_start) -> ext::number<long>
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_olist_element);
        return d->start = new_start;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_olist_element::set_type(ext::string new_type) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_olist_element);
        return d->type = std::move(new_type);
    CE_REACTIONS_METHOD_EXE
}



auto html::elements::html_olist_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) convertsion = v8pp::class_<html_olist_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .property("reversed", &html_olist_element::get_reversed, &html_olist_element::set_reversed)
        .property("start", &html_olist_element::get_start, &html_olist_element::set_start)
        .property("type", &html_olist_element::get_type, &html_olist_element::set_type)
        .auto_wrap_objects();
}

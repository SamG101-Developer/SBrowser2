#include "html_mod_element.hpp"
#include "html_mod_element_private.hpp"

#include "dom/detail/customization_internals.hpp"


html::elements::html_mod_element::html_mod_element()
{
    INIT_PIMPL(html_mod_element);
    HTML_CONSTRUCTOR
}


auto html::elements::html_mod_element::get_cite() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_mod_element);
        return d->cite;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_mod_element::get_date_time() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_mod_element);
        return d->date_time;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_mod_element::set_cite(ext::string new_cite) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_mod_element);
        return d->cite = std::move(new_cite);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_mod_element::set_date_time(ext::string new_date_time) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_mod_element);
        return d->date_time = std::move(new_date_time);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_mod_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_mod_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .property("cite", &html_mod_element::get_cite, &html_mod_element::set_cite)
        .property("dateTime", &html_mod_element::get_date_time, &html_mod_element::set_date_time)
        .auto_wrap_objects();

    return std::move(conversion);
}

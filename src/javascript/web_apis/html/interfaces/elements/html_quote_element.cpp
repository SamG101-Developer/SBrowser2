#include "html_quote_element.hpp"
#include "html_quote_element_private.hpp"




html::elements::html_quote_element::html_quote_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_quote_element::get_cite() const -> ext::string_view
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(const html_quote_element);
        return d->cite;
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_quote_element::set_cite(ext::string new_cite) -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        ACCESS_PIMPL(html_quote_element);
        return d->cite = std::move(new_cite);
    CE_REACTIONS_METHOD_EXE
}


auto html::elements::html_quote_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_quote_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .property("cite", &html_quote_element::get_cite, &html_quote_element::set_cite)
        .auto_wrap_objects();

    return std::move(conversion);
}

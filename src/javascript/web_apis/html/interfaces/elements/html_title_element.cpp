#include "html_title_element.hpp"
#include "html_title_element_private.hpp"





html::elements::html_title_element::html_title_element()
{
    INIT_PIMPL(html_title_element);
    HTML_CONSTRUCTOR;
}


auto html::elements::html_title_element::get_text() const -> ext::string
{
    // The 'text' of a HTMLTitleElement is the child text content of the element; this is the concatenated text of all
    // the children Text nodes that have this node as an ancestor.
    return dom::detail::child_text_content(this);
}


auto html::elements::html_title_element::set_text(ext::string new_text) -> ext::string
{
    // To set the 'text' of a HTMLTitleElement, all the string content beneath this element is replaced with the new
    // 'val' text.
    dom::detail::string_replace_all(std::move(new_text), this);
}


auto html::elements::html_title_element::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<html_title_element>{isolate}
        .ctor<>()
        .inherit<html_element>()
        .property("text", &html_title_element::get_text, &html_title_element::set_text)
        .auto_wrap_objects();

    return std::move(conversion);
}

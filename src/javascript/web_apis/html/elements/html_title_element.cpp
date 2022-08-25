#include "html_title_element.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/detail/tree_internals.hpp"


html::elements::html_title_element::html_title_element()
{
    HTML_CONSTRUCTOR
}


auto html::elements::html_title_element::get_text()
        const -> decltype(this->text)::value_t
{
    // the 'text' of a HTMLTitleElement is the child text content of the element; this is the concatenated text of all
    // the children Text nodes that have this node as an ancestor
    return dom::detail::child_text_content(this);
}


auto html::elements::html_title_element::set_text(
        const ext::string& val)
        -> void
{
    // to set the 'text' of a HTMLTitleElement, all the string content beneath this element is replaced with the new
    // 'val' text
    dom::detail::string_replace_all(val, this);
}


auto html::elements::html_title_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_title_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .var("text", &html_title_element::text, false)
            .auto_wrap_objects();
}

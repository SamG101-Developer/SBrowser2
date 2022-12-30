module;
#include "ext/macros.hpp"


module apis.dom.text;

import ext.core;


dom::text::text(
        ext::string&& new_data)
{
    INIT_PIMPL(text);
    ACCESS_PIMPL(text);
    d->data = std::move(new_data);
}


auto dom::text::split_text(
        ext::number<ulong> offset)
        -> std::unique_ptr<text>
{
    // Split the text node at the index 'offset', and return the 2nd half of the split, ie a Text node containing all
    // data after the split (this Text node remains the same)
    return std::move(dom::detail::split(this, offset));
}


auto dom::text::get_node_name() const -> ext::string
{
    // The 'node_name' getter returns the fixed string "#text". Apply custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        return u"#text";
    CE_REACTIONS_METHOD_EXE
}


auto dom::text::get_whole_text() const -> ext::string
{
    // TODO -> create contiguous_text_content(...) in detail
    // The whole text of a Text node is the contiguous node data ie the combined data of all the contiguous Text nodes
    dom::detail::contiguous_text_nodes(this)
            | ranges::views::transform(&text_private::data, ext::get_pimpl)
            | ranges::to<ext::string>();
}


auto dom::text::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .ctor<>()
        .ctor<ext::string_view>()
        .inherit<character_data>()
        .inherit<mixins::slottable>()
        .function("splitText", &text::split_text)
        .property("wholeText", &text::get_whole_text)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

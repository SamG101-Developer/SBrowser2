#include "text.hpp"

#include "dom/nodes/character_data.hpp"
#include "dom/detail/customization_internals.hpp"
#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include <range/v3/view/transform.hpp>
#include <range/v3/to_container.hpp>

#include <QtWidgets/QVBoxLayout>


dom::nodes::text::text(
        ext::string&& new_data)
{
    INIT_PIMPL(text);
    ACCESS_PIMPL(text);
    d->data = std::move(new_data);
}


auto dom::nodes::text::split_text(
        ext::number<ulong> offset)
        -> std::unique_ptr<text>
{
    // split the text node at the index 'offset', and return the 2nd half of the split, ie a Text node containing all
    // data after the split (this Text node remains the same)
    return std::move(dom::detail::split(this, offset));
}


auto dom::nodes::text::get_node_name() const -> ext::string
{
    CE_REACTIONS_METHOD_DEF
        return "#text";
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::text::get_whole_text() const -> ext::string
{
    // TODO -> create contiguous_text_content(...) in detail
    // the whole text of a Text node is the contiguous node data ie the combined data of all the contiguous Text nodes
    dom::detail::contiguous_text_nodes(this)
            | ranges::views::transform([](nodes::character_data* node) {return node->d_func()->data;})
            | ranges::to<ext::string>();
}


auto dom::nodes::text::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<text>{isolate}
            .ctor<>()
            .ctor<ext::string_view>()
            .inherit<character_data>()
            .inherit<mixins::slottable>()
            .function("splitText", &text::split_text)
            .property("wholeText", &text::get_whole_text)
            .auto_wrap_objects();

    return std::move(conversion);
}

#include "text.hpp"

#include "dom/detail/text_internals.hpp"
#include "dom/detail/tree_internals.hpp"

#include <range/v3/view/transform.hpp>
#include <range/v3/to_container.hpp>

#include <QtWidgets/QVBoxLayout>


dom::nodes::text::text(ext::string&& new_data)
{
    bind_get(whole_text);

    data = std::move(new_data);
}


auto dom::nodes::text::split_text(
        const ext::number<ulong>& offset)
        -> text
{
    // split the text node at the index 'offset', and return the 2nd half of the split, ie a Text node containing all
    // data after the split (this Text node remains the same)
    return dom::detail::split(this, offset);
}


auto dom::nodes::text::get_whole_text()
        const -> decltype(this->whole_text)::value_t
{
    // the whole text of a Text node is the contiguous node data ie the combined data of all the contiguous Text nodes
    dom::detail::contiguous_text_nodes(this) // TODO -> create contiguous_text_content(...) in detail
            | ranges::views::transform([](nodes::text* node) {return node->data();})
            | ranges::to<ext::string>();
}


auto dom::nodes::text::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<text>{isolate}
            .ctor<>()
            .ctor<ext::string_view>()
            .inherit<character_data>()
            .inherit<mixins::slottable>()
            .function("splitText", &text::split_text)
            .var("wholeText", &text::whole_text, true)
            .auto_wrap_objects();
}

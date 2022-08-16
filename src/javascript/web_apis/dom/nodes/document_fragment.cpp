#include "document_fragment.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/detail/tree_internals.hpp"


auto dom::nodes::document_fragment::get_text_content()
        const -> ext::string
{
    // the text content of a DocumentFragment is the descendant text content of it; this is because the DocumentFragment
    // is effectively a Range of elements, including Text nodes, so it makes sense that the text content of the
    // container (DocumentFragment) is the entire text content that it is containing
    return detail::descendant_text_content(this);
}


auto dom::nodes::document_fragment::set_text_content(
        ext::string_view val)
        -> void
{
    // setting the text content of a DocumentFragment has to replace the text that the 'text_content' getter gets; in
    // this case it's the descendant text content of the DocumentFragment. this is done by replacing all the text under
    // the node
    detail::string_replace_all(val, this);
}


auto dom::nodes::document_fragment::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<document_fragment>{isolate}
            .ctor<>()
            .inherit<node>()
            .inherit<mixins::non_element_parent_node>()
            .inherit<parentable_node>()
            .auto_wrap_objects();
}

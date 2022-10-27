#include "document_fragment.hpp"
#include "document_fragment_private.hpp"

#include "dom/detail/customization_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/detail/tree_internals.hpp"


dom::nodes::document_fragment::document_fragment()
{
    INIT_PIMPL(document_fragment);
}


auto dom::nodes::document_fragment::get_node_name() const -> ext::string
{
    // The 'node_name' getter returns the fixed string "#document-origin". Apply custom element reactions to this
    // getter.
    CE_REACTIONS_METHOD_DEF
        return u8"#document-fragment";
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::document_fragment::get_node_value() const -> ext::string
{
    // The 'node_vaue' getter returns the fixed string "". Apply custom element reactions to this getter.
    CE_REACTIONS_METHOD_DEF
        return u8"";
    CE_REACTIONS_METHOD_EXE
}


auto dom::nodes::document_fragment::get_text_content() const -> ext::string
{
    // The 'text_content' getter returns the 'descendant_text_content' of this node
    return detail::descendant_text_content(this);
}


auto dom::nodes::document_fragment::set_text_content(ext::string new_text_content) -> ext::string
{
    // The 'text_content' setter runs a 'string_replace_all' detail method that replaces all the textual content of
    // nodes under this node in the tree (descendants of this DocumentFragment only)
    detail::string_replace_all(new_text_content, this);
}


auto dom::nodes::document_fragment::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<document_fragment>{isolate}
        .inherit<node>()
        .inherit<mixins::non_element_parent_node>()
        .inherit<mixins::parentable_node>()
        .ctor<>()
        .auto_wrap_objects();

    return std::move(conversion);
}

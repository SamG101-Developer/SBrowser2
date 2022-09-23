#include "document_fragment.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/detail/tree_internals.hpp"


dom::nodes::document_fragment::document_fragment() : INIT_PIMPL
{}


auto dom::nodes::document_fragment::get_text_content() const -> ext::string
{return detail::descendant_text_content(this);}


auto dom::nodes::document_fragment::set_text_content(ext::string new_text_content) -> ext::string
{detail::string_replace_all(new_text_content, this);}


auto dom::nodes::document_fragment::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<document_fragment>{isolate}
        .inherit<node>()
        .inherit<mixins::non_element_parent_node>()
        .inherit<parentable_node>()
        .ctor<>()
        .auto_wrap_objects();

    return std::move(conversion);
}

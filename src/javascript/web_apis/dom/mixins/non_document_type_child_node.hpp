#ifndef SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP
#define SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP

#include <web_apis/dom_object.hpp>
namespace dom::mixins {template <typename T> class non_document_type_child_node;}

namespace dom::nodes {class element;}


template <typename T>
class dom::mixins::non_document_type_child_node
        : public virtual web_apis::dom_object
{
public constructors:
    using web_apis::dom_object::dom_object;
    non_document_type_child_node();

public js_properties:
    ext::property<nodes::element*> previous_element_sibling;
    ext::property<nodes::element*> next_element_sibling;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    [[nodiscard]] auto get_previous_element_sibling() const -> nodes::element*;
    [[nodiscard]] auto get_next_element_sibling() const -> nodes::element*;
};


#endif //SBROWSER2_NON_DOCUMENT_TYPE_CHILD_NODE_HPP

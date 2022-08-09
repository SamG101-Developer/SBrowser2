#ifndef SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP
#define SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class document_or_element_node;}

#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class element;}


class dom::mixins::document_or_element_node
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(document_or_element_node);

public js_methods:
    [[nodiscard]] auto get_elements_by_class_name(ext::string_view class_names) const -> ranges::any_view<nodes::element*>;
    [[nodiscard]] auto get_elements_by_tag_name(ext::string_view qualified_name) const -> ranges::any_view<nodes::element*>;
    [[nodiscard]] auto get_elements_by_tag_name_ns(ext::string_view namespace_, ext::string_view local_name) const -> ranges::any_view<nodes::element*>;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP

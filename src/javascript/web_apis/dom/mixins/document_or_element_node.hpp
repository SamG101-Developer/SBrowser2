#ifndef SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP
#define SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP

#include "dom_object.hpp"
namespace dom::mixins {class document_or_element_node;}
namespace dom::mixins {class document_or_element_node_private;}

#include "ext/vector.hpp"
#include <range/v3/view/any_view.hpp>
namespace dom::nodes {class element;}


class dom::mixins::document_or_element_node
        : public virtual dom_object
{
public constructors:
    document_or_element_node();
    MAKE_PIMPL(document_or_element_node);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    _EXT_NODISCARD auto get_elements_by_class_name(ext::string_view class_names) const -> ranges::any_view<nodes::element*>;
    _EXT_NODISCARD auto get_elements_by_tag_name(ext::string_view qualified_name) const -> ranges::any_view<nodes::element*>;
    _EXT_NODISCARD auto get_elements_by_tag_name_ns(ext::string_view namespace_, ext::string_view local_name) const -> ranges::any_view<nodes::element*>;
};


#endif //SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP

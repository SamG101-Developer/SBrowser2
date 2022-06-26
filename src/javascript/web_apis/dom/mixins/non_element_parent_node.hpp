#ifndef SBROWSER2_NON_ELEMENT_PARENT_NODE_HPP
#define SBROWSER2_NON_ELEMENT_PARENT_NODE_HPP

#include <web_apis/dom_object.hpp>
namespace dom::mixins {class non_element_parent_node;}

namespace dom::nodes {class element;}


class dom::mixins::non_element_parent_node
        : public virtual web_apis::dom_object
{
public js_methods:
    auto get_element_by_id(ext::string_view id) -> nodes::element*;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_NON_ELEMENT_PARENT_NODE_HPP

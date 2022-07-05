#ifndef SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP
#define SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP

#include <web_apis/dom_object.hpp>
namespace dom::mixins {class document_or_element_node;}

#include <ext/vector.hpp>
#include <range/v3/view/ref.hpp>
namespace dom::nodes {class element;}


class dom::mixins::document_or_element_node
        : public virtual web_apis::dom_object
{
public js_methods:
    auto get_elements_by_class_name(ext::string_view class_names) -> range_v3_view auto;
    auto get_elements_by_tag_name(ext::string_view qualified_name) -> range_v3_view auto;
    auto get_elements_by_tag_name_ns(ext::string_view namespace_, ext::string_view local_name) -> range_v3_view auto;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_DOCUMENT_OR_ELEMENT_NODE_HPP

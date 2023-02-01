module;
#include "ext/macros.hpp"


export module apis.dom.mixins.document_or_element_node;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom::mixins, document_or_element_node)
        : public virtual dom_object
{
public constructors:
    document_or_element_node();
    MAKE_PIMPL(document_or_element_node);
    MAKE_V8_AVAILABLE(MIXIN);

private js_methods:
    _EXT_NODISCARD auto get_elements_by_class_name(ext::string_view class_names) const -> ranges::any_helpful_view<element*>;
    _EXT_NODISCARD auto get_elements_by_tag_name(ext::string_view qualified_name) const -> ranges::any_helpful_view<element*>;
    _EXT_NODISCARD auto get_elements_by_tag_name_ns(ext::string_view namespace_, ext::string_view local_name) const -> ranges::any_helpful_view<element*>;
};

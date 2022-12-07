module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/extended_attributes.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.mixins.document_or_element_node;
import apis._.dom_object;
import ext.string;
import ext.ranges;
import ext.tuple;
import js.env.module_type;

namespace dom {class element;}


DEFINE_PUBLIC_CLASS(dom, document_or_element_node) final
        : public virtual dom_object
{
public constructors:
    document_or_element_node();
    MAKE_PIMPL(document_or_element_node);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    _EXT_NODISCARD auto get_elements_by_class_name(ext::string_view class_names) const -> ranges::any_helpful_view<element*>;
    _EXT_NODISCARD auto get_elements_by_tag_name(ext::string_view qualified_name) const -> ranges::any_helpful_view<element*>;
    _EXT_NODISCARD auto get_elements_by_tag_name_ns(ext::string_view namespace_, ext::string_view local_name) const -> ranges::any_helpful_view<element*>;
};

module;
#include "ext/macros.hpp"


export module apis.dom.document_fragment;
import apis.dom.node;
import apis.dom.mixins.non_element_parent_node;
import apis.dom.mixins.parentable_node;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, document_fragment)
        : public dom::node
        , public dom::non_element_parent_node
        , public dom::parentable_node
{
public friends:
    friend class dom::range;

public:
    DOM_CTORS(document_fragment);
    MAKE_PIMPL(document_fragment);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return DOCUMENT_FRAGMENT_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
    DEFINE_GETTER(node_value, ext::string) override;
    DEFINE_GETTER(text_content, ext::string) override;

    DEFINE_SETTER(node_value, ext::string) override {}
    DEFINE_SETTER(text_content, ext::string) override;
};

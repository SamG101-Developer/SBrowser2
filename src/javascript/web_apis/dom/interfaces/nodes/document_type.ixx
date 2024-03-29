module;
#include "ext/macros.hpp"


export module apis.dom.document_type;
import apis.dom.node;
import apis.dom.mixins.child_node;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, document_type) final
        : public dom::node
        , public dom::child_node
{
public friends:
    friend class dom::dom_implementation;

public constructors:
    DOM_CTORS(document_type);
    MAKE_PIMPL(document_type);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return DOCUMENT_TYPE_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
    DEFINE_GETTER(node_value, ext::string) override {return u"";}
    DEFINE_GETTER(text_content, ext::string) override {return u"";}

    DEFINE_SETTER(node_value, ext::string) override {}
    DEFINE_SETTER(text_content, ext::string) override {}

    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(public_id, ext::string_view);
    DEFINE_GETTER(system_id, ext::string_view);
};

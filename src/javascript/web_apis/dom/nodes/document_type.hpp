#ifndef SBROWSER2_DOCUMENT_TYPE_HPP
#define SBROWSER2_DOCUMENT_TYPE_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/child_node.hpp"
namespace dom::nodes {class document_type;}
namespace dom::nodes {class document_type_private;}

namespace dom::other {class dom_implementation;}


class dom::nodes::document_type final
        : public node
        , public mixins::child_node
{
public friends:
    friend class dom::other::dom_implementation;

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


#endif //SBROWSER2_DOCUMENT_TYPE_HPP

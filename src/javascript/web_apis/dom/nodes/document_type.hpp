#ifndef SBROWSER2_DOCUMENT_TYPE_HPP
#define SBROWSER2_DOCUMENT_TYPE_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/child_node.hpp"
namespace dom::nodes {class document_type;}


#include "dom/nodes/document_type_private.hpp"


class dom::nodes::document_type final
        : public node
        , public mixins::child_node
{

public constructors:
    document_type();
    MAKE_PIMPL(document_type);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return DOCUMENT_TYPE_NODE;}
    DEFINE_GETTER(node_name, ext::string) override {return d_ptr->name;}
    DEFINE_GETTER(node_value, ext::string) override {return "";}
    DEFINE_GETTER(text_content, ext::string) override {return "";}

    DEFINE_SETTER(node_value, ext::string) override {}
    DEFINE_SETTER(text_content, ext::string) override {}

    DEFINE_GETTER(name, ext::string) {return d_ptr->name;}
    DEFINE_GETTER(public_id, ext::string) {return d_ptr->public_id;}
    DEFINE_GETTER(system_id, ext::string) {return d_ptr->system_id;}
};


#endif //SBROWSER2_DOCUMENT_TYPE_HPP

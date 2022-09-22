#ifndef SBROWSER2_DOCUMENT_FRAGMENT_HPP
#define SBROWSER2_DOCUMENT_FRAGMENT_HPP

#include "dom/nodes/node.hpp"
#include "dom/mixins/non_element_parent_node.hpp"
#include "dom/mixins/parentable_node.hpp"
namespace dom::nodes {class document_fragment;}

#include "dom/nodes/document_fragment_private.hpp"


class dom::nodes::document_fragment
        : public node
        , public mixins::non_element_parent_node
        , public mixins::parentable_node
{
public:
    document_fragment();

private cpp_members:
    MAKE_PIMPL(document_fragment);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(node_type) override {return DOCUMENT_FRAGMENT_NODE;}
    DEFINE_CUSTOM_GETTER(node_name) override {return "#document-fragment";}
    DEFINE_CUSTOM_GETTER(node_value) override {return "";}
    DEFINE_CUSTOM_GETTER(text_content) override;

    DEFINE_CUSTOM_SETTER(node_value) override {}
    DEFINE_CUSTOM_SETTER(text_content) override;
};


#endif //SBROWSER2_DOCUMENT_FRAGMENT_HPP

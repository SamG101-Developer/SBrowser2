#ifndef SBROWSER2_DOCUMENT_HPP
#define SBROWSER2_DOCUMENT_HPP

#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/mixins/parent_node.hpp>
namespace dom::nodes {class document;}


class dom::nodes::document
        : public node
        , public mixins::parent_node
{
private cpp_accessors:
    auto get_node_name() const -> ext::string override {return "#document";}
};


#endif //SBROWSER2_DOCUMENT_HPP

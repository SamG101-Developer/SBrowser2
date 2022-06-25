#ifndef SBROWSER2_DOCUMENT_FRAGMENT_HPP
#define SBROWSER2_DOCUMENT_FRAGMENT_HPP

#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/mixins/parent_node.hpp>
namespace dom::nodes {class document_fragment;}


class dom::nodes::document_fragment
        : public node
        , public mixins::parent_node
{

};


#endif //SBROWSER2_DOCUMENT_FRAGMENT_HPP

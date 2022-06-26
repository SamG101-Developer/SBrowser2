#ifndef SBROWSER2_DOCUMENT_FRAGMENT_HPP
#define SBROWSER2_DOCUMENT_FRAGMENT_HPP

#include <web_apis/dom/nodes/node.hpp>
#include <web_apis/dom/mixins/non_element_parent_node.hpp>
#include <web_apis/dom/mixins/parentable_node.hpp>
namespace dom::nodes {class document_fragment;}


class dom::nodes::document_fragment
        : public node
        , public mixins::non_element_parent_node
        , public mixins::parentable_node
{

};


#endif //SBROWSER2_DOCUMENT_FRAGMENT_HPP

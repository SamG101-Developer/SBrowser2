#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_COMMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_COMMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/character_data_private.hpp"


DEFINE_PRIVATE_CLASS(dom::nodes, comment)
        : character_data_private
{
    MAKE_QIMPL(comment);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_COMMENT_PRIVATE_HPP

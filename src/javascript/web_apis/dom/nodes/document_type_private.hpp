#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_TYPE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_TYPE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(dom::nodes, document_type)
{
    ext::string name;
    ext::string public_id;
    ext::string system_id;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_DOCUMENT_TYPE_PRIVATE_HPP

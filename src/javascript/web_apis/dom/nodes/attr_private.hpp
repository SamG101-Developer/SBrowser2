#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ATTR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ATTR_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/node_private.hpp"

#include "ext/string.hpp"
namespace dom::nodes {class element;}


DEFINE_PRIVATE_CLASS(dom::nodes, attr)
        : node_private
{
    MAKE_QIMPL(attr);

    ext::string namespace_;
    ext::string namespace_prefix;
    ext::string local_name;
    ext::string value;
    dom::nodes::element* element;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_ATTR_PRIVATE_HPP

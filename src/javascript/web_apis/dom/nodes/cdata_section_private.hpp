#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CDATA_SECTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CDATA_SECTION_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/text_private.hpp"


DEFINE_PRIVATE_CLASS(dom::nodes, cdata_section)
        : text_private
{
    MAKE_QIMPL(cdata_section);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_CDATA_SECTION_PRIVATE_HPP

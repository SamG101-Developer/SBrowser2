#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_IMPLEMENTATION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_IMPLEMENTATION_PRIVATE_HPP

#include "dom_object_private.hpp"

#include "ext/pimpl.hpp"

namespace dom::nodes {class document;}


DEFINE_PRIVATE_CLASS(dom::other, dom_implementation) : virtual dom_object_private
{
    nodes::document* document;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_IMPLEMENTATION_PRIVATE_HPP
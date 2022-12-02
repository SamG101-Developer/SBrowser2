#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_IMPLEMENTATION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_IMPLEMENTATION_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/memory.ixx"
namespace dom::nodes {class document;}


DEFINE_PRIVATE_CLASS(dom::other, dom_implementation)
        : virtual dom_object_private
{
    MAKE_QIMPL(dom_implementation);

    std::observer_ptr<nodes::document> document;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_OTHER_DOM_IMPLEMENTATION_PRIVATE_HPP

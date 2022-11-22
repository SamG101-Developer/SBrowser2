#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_CONTROLLER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_CONTROLLER_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

namespace dom::abort {class abort_signal;}


DEFINE_PRIVATE_CLASS(dom::abort, abort_controller)
        : virtual dom_object_private
{
    std::unique_ptr<abort_signal> signal;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_CONTROLLER_PRIVATE_HPP

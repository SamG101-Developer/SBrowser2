#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_CONTROLLER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_CONTROLLER_PRIVATE_HPP

#include "ext/pimpl.hpp"

namespace dom::abort {class abort_signal;}


DEFINE_PRIVATE_CLASS(dom::abort, abort_controller)
{
    std::unique_ptr<abort_signal> signal;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_CONTROLLER_PRIVATE_HPP

#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_SIGNAL_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_SIGNAL_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include "ext/any.hpp"


DEFINE_PRIVATE_CLASS(dom::abort, abort_signal) : public event_target_private
{
    detail::abort_signal_callbacks_t abort_algorithms;
    ext::any abort_reason;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_SIGNAL_PRIVATE_HPP

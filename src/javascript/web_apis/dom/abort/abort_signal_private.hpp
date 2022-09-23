#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_SIGNAL_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_SIGNAL_PRIVATE_HPP

#include "dom/nodes/event_target_private.hpp"

#include "ext/any.hpp"
#include "ext/pimpl.hpp"
#include INCLUDE_INNER_TYPES(dom)


DEFINE_PRIVATE_CLASS(dom::abort, abort_signal) : public event_target_private
{
    detail::abort_signal_callbacks_t abort_algorithms;
    ext::any abort_reason;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_SIGNAL_PRIVATE_HPP

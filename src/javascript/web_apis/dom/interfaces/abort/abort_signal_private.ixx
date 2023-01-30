module;
#include "ext/macros.hpp"


export module apis.dom.abort_signal:p;
import apis.dom.event_target;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, abort_signal)
        : event_target_private
{
public:
    MAKE_QIMPL(abort_signal);

public:
    detail::abort_signal_callbacks_t abort_algorithms;
    ext::any abort_reason;
};

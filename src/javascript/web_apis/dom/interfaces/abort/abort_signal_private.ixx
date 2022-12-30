module;
#include "ext/macros.hpp"


export module apis.dom.abort_signal:p;
import apis.dom.event_target;
import apis.dom.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, abort_signal)
        : event_target_private
{
public:
    MAKE_QIMPL(abort_signal);

public:
    auto aborted() const -> ext::boolean {return abort_reason.has_value();}
    auto follow_signal(abort_signal* parent_signal) -> void;
    auto signal_abort(ext::any&& reason) -> void;

public:
    detail::abort_signal_callbacks_t abort_algorithms;
    ext::any abort_reason;
};

export module dom.abort_signal_private;

import dom.event_target;
import ext.any;
import ext.boolean;


DEFINE_PRIVATE_CLASS(dom::abort, abort_signal)
        : nodes::event_target_private
{
    MAKE_QIMPL(abort_signal);

    auto aborted() const -> ext::boolean {return abort_reason.has_value();}
    auto follow_signal(abort_signal* parent_signal) {/* TODO */}

    detail::abort_signal_callbacks_t abort_algorithms;
    ext::any abort_reason;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_ABORT_ABORT_SIGNAL_PRIVATE_IXX

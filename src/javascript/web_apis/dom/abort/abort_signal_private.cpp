module;
#include "ext/macros/language_shorthand.hpp"
#include <range/v3/view/for_each.hpp>


module apis.dom.abort_signal_private;
import apis.dom.abort_signal;
import ext.core;


auto dom::abort_signal_private::signal_abort(ext::any&& reason) -> void
{
    // Can't abort an already aborted AbortSignal, so return and dont do anything else. Otherwise, abort the signal,
    // execute all the abort algorithms in order, and clear the list of algorithms.
    return_if(aborted());
    abort_reason = std::move(reason);
    abort_algorithms | ranges::views::for_each(ext::invoke);
    abort_algorithms.clear();

    // Fire an event to notify that the signal abort has happened; the event is directed at the signal that has just
    // been aborted.
    fire_event(u"Abort");
}


auto dom::abort_signal_private::follow_signal(abort_signal* parent_signal) -> void
{
    return_if(aborted());

    // Abort if the 'parent_signal' has aborted, otherwise when the 'parent_signal' does abort, tell this signal to
    // abort as well, using the reason of the 'parent_signal', by adding this method to the 'parent_signal's abort
    // algorithms.
    auto abort_this_following_parent =
            [this, &parent_signal] mutable
            {signal_abort(std::move(parent_signal->d_func()->abort_reason));};

    if (parent_signal->d_func()->aborted())
        signal_abort(std::move(parent_signal->d_func()->abort_reason));
    else
        parent_signal->d_func()->abort_algorithms.emplace_back(std::move(abort_this_following_parent));
}

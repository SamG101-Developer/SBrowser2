#include "aborting_internals.hpp"


#include "dom/abort/abort_signal.hpp"
#include "dom/abort/abort_signal_private.hpp"
#include "dom/detail/event_internals.hpp"

#include <range/v3/view/for_each.hpp>


auto dom::detail::signal_abort(
        abort::abort_signal* const signal,
        const ext::any& reason)
        -> void
{
    // Can't abort an already aborted AbortSignal, so return and dont do anything else. Otherwise, abort the signal,
    // execute all the abort algorithms in order, and clear the list of algorithms.
    return_if(signal->d_func()->aborted());
    signal->d_func()->abort_reason = reason;
    signal->d_func()->abort_algorithms | ranges::views::for_each(ext::invoke);
    signal->d_func()->abort_algorithms.clear();

    // Fire an event to notify that the signal abort has happened; the event is directed at the signal that has just
    // been aborted.
    fire_event(u"Abort", signal);
}


auto dom::detail::follow_signal(
        abort::abort_signal* const following_signal,
        abort::abort_signal* const parent_signal)
        -> void
{
    return_if(following_signal->d_func()->aborted());

    // Abort the 'following_signal' if the 'parent_signal' has aborted, otherwise when the 'parent_signal' does abort,
    // tell the 'following_signal' to abort as well, using the reason of the parent signal, by adding this method to the
    // 'parent_signal's abort algorithms.
    parent_signal->d_func()->aborted()
            ? signal_abort(following_signal, parent_signal->d_func()->abort_reason)
            : parent_signal->d_func()->abort_algorithms.push_back(
                    [&following_signal, &parent_signal]
                    {signal_abort(following_signal, parent_signal->d_func()->abort_reason);});
}

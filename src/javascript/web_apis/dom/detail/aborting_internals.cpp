#include "aborting_internals.hpp"

#include "ext/any.hpp"
#include "dom/abort/abort_signal.hpp"
#include "dom/abort/abort_signal_private.hpp"
#include "dom/detail/event_internals.hpp"

#include <range/v3/view/for_each.hpp>


auto dom::detail::signal_abort(
        abort::abort_signal* const signal,
        const ext::any& reason)
        -> void
{
    return_if(detail::is_signal_aborted(signal));

    // abort the signal, execute all the abort algorithms, and clear the list of algorithms
    signal->d_func()->abort_reason = reason;
    signal->d_func()->abort_algorithms | ranges::views::for_each(ext::invoke{});
    signal->d_func()->abort_algorithms.clear();

    // fire an event to notify that the signal abort has happened; the event is directed at the signal that has
    // been aborted
    fire_event(u"Abort", signal);
}


auto dom::detail::follow_signal(
        abort::abort_signal* const following_signal,
        abort::abort_signal* const parent_signal)
        -> void
{
    return_if(following_signal->d_func()->aborted());

    // abort the following signal if the parent signal has aborted, otherwise when the parent signal does abort, tell
    // the following signal to abort as well, using the reason of the parent signal
    parent_signal->d_func()->aborted()
            ? signal_abort(following_signal, parent_signal->d_func()->abort_reason)
            : parent_signal->d_func()->abort_algorithms.push_back(
                    [&following_signal, &parent_signal]
                    {signal_abort(following_signal, parent_signal->d_func()->abort_reason);});
}

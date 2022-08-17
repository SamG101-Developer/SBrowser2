#include "aborting_internals.hpp"

#include "dom/abort/abort_signal.hpp"
#include "dom/detail/event_internals.hpp"

#include <range/v3/algorithm/for_each.hpp>


auto dom::detail::signal_abort(
        abort::abort_signal* const signal,
        const ext::any& reason)
        -> void
{
    return_if(signal->aborted());

    // abort the signal, execute all the abort algorithms, and clear the list of algorithms
    signal->reason = reason;
    ranges::for_each(signal->m_abort_algorithms, ext::invoke{});
    signal->m_abort_algorithms.clear();

    // fire an event to notify that the signal abort has happened; the event is directed at the signal that has
    // been aborted
    fire_event("Abort", signal);
}


auto dom::detail::follow_signal(
        abort::abort_signal* const following_signal,
        abort::abort_signal* const parent_signal)
        -> void
{
    return_if(following_signal->aborted());

    // abort the following signal if the parent signal has aborted, otherwise when the parent signal does abort, tell
    // the following signal to abort as well, using the reason of the parent signal
    parent_signal->aborted()
            ? signal_abort(following_signal, parent_signal->reason())
            : parent_signal->m_abort_algorithms.push_back([&f = following_signal, &p = parent_signal] {signal_abort(f, p->reason());});
}

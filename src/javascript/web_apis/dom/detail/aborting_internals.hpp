#ifndef SBROWSER2_ABORTING_INTERNALS_HPP
#define SBROWSER2_ABORTING_INTERNALS_HPP

#include <ext/any.hpp>
#include <web_apis/dom/abort/abort_signal.hpp>
#include <web_apis/dom/detail/aborting_internals.hpp>
namespace dom::abort {class abort_signal;}


namespace dom::detail::aborting_internals
{
    auto signal_abort(
            abort::abort_signal* signal,
            ext::any_view reason)
            -> void;

    auto follow_signal(
            abort::abort_signal* following_signal,
            abort::abort_signal* parent_signal)
            -> void;
}


auto dom::detail::aborting_internals::signal_abort(
        abort::abort_signal* signal,
        ext::any_view reason)
        -> void
{
    return_if(signal->aborted);

    // abort the signal, execute all the abort algorithms, and clear the list of algorithms
    signal->reason = reason;
    std::ranges::for_each(signal->m_abort_algorithms, [] (const abort::abort_signal::abort_signal_callback_t& callback) {callback();});
    signal->m_abort_algorithms.clear();

    // fire an event to notify that the signal abort has happened; the event is directed at the signal that has
    // been aborted
    event_internals::fire_event<>("Abort", signal);
}


auto dom::detail::aborting_internals::follow_signal(
        abort::abort_signal* following_signal,
        abort::abort_signal* parent_signal)
        -> void
{
    return_if(following_signal->aborted);

    // abort the following signal if the parent signal has aborted, otherwise when the parent signal does abort, tell
    // the following signal to abort as well, using the reason of the parent signal
    parent_signal->aborted
            ? signal_abort(following_signal, parent_signal->reason)
            : parent_signal->m_abort_algorithms.push_back([&f = following_signal, &p = parent_signal] {signal_abort(f, p->reason);});
}



#endif //SBROWSER2_ABORTING_INTERNALS_HPP

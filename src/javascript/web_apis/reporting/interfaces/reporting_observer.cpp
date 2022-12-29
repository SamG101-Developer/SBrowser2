module;
#include "ext/macros/macros.hpp"


module apis.reporting.reporting_observer_private;


reporting::reporting_observer::reporting_observer(
        detail::reporting_observer_callback_t&& callback,
        detail::reporting_observer_options_t&& options)
{
    INIT_PIMPL(reporting_observer);
    ACCESS_PIMPL(reporting_observer);

    d->callback = std::move(callback);
    d->options = std::move(options);
}


auto reporting::reporting_observer::observe() -> void
{
    ACCESS_PIMPL(reporting_observer);
    auto e = js::env::env::relevant(this);
    // TODO : Global work

    return_if (!d->options[u"buffered"].to<ext::boolean>());
    d->options[u"buffered"] = false;

    // TODO : Global work
}


auto reporting::reporting_observer::take_records() -> ext::vector<report*>
{
    ACCESS_PIMPL(reporting_observer);
    decltype(auto) container = std::move(d->report_queue);
    d->report_queue = {};
    return {std::make_move_iterator(&container.front()), std::make_move_iterator(&container.back())};
}

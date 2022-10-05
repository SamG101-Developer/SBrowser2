#include "performance_observer.hpp"
#include "performance_observer_private.hpp"

#include "ext/ranges.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include INCLUDE_INNER_TYPES(performance_timeline)

#include "dom/detail/exception_internals.hpp"

#include <range/v3/algorithm/remove_if.hpp>


auto performance_timeline::performance_observer::observe(
        detail::performance_observer_init_t&& options)
        -> void
{
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&options] {return !options.contains("entryTypes") && !options.contains("types");},
            "The 'options' must contain an 'entryTypes' or 'type' value");

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&options] {return options.contains("entryTypes") && options.size() > 1;},
            "The 'options' mustn't contain any other values if 'entryTypes' are provided");

    ACCESS_PIMPL(performance_observer);

    if (d->observer_type == detail::performance_observer_type_t::UNDEFINED && options.contains("entryTypes"))
        d->observer_type = detail::performance_observer_type_t::MULTIPLE;

    if (d->observer_type == detail::performance_observer_type_t::UNDEFINED && options.contains("types"))
        d->observer_type = detail::performance_observer_type_t::SINGLE;

    dom::detail::throw_v8_exception_formatted<INVALID_MODIFICATION_ERR>(
            [type = d->observer_type, &options] {return type == detail::performance_observer_type_t::SINGLE && options.contains("entryTypes");},
            "");

    dom::detail::throw_v8_exception_formatted<INVALID_MODIFICATION_ERR>(
            [type = d->observer_type, &options] {return type == detail::performance_observer_type_t::MULTIPLE && options.contains("type");},
            "");

    d->requires_dropped_entries = true;

    if (d->observer_type == detail::performance_observer_type_t::MULTIPLE)
    {

        decltype(auto) entry_types = options["entryTypes"].to<ext::vector<ext::string>>();
        entry_types |= ranges::actions::remove_if(BIND_FRONT(ranges::negate_contains, get_supported_entry_types()));
        return_if (entry_types.empty()); // TODO : report to console that observer has aborted
        // TODO : global
    }

    else
    {
        ASSERT(d->observer_type == detail::performance_observer_type_t::SINGLE);
        decltype(auto) types = options["types"].to<ext::string>();
        return_if (!ranges::contains(get_supported_entry_types(), std::move(types)));

        // TODO : global
    }
}


auto performance_timeline::performance_observer::disconnect()
        -> void
{
    // TODO : global
    ACCESS_PIMPL(performance_observer);
    d->observer_buffer.clear();
    d->options_list.clear(); // TODO : ???
}


auto performance_timeline::performance_observer::take_records()
        -> ext::vector<performance_entry*>
{
    ACCESS_PIMPL(performance_observer);
    decltype(auto) current_records = std::move(d->observer_buffer);
    d->observer_buffer = {};
    return std::move(current_records);
}

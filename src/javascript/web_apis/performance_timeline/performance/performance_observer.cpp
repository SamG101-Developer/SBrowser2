module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"
#include <range/v3/action/remove_if.hpp>
#include <range/v3/algorithm/contains.hpp>


module apis.performance_timeline.performance_observer;
import apis.performance_timeline.performance_observer_private;
import apis.performance_timeline.types;

import apis.dom.detail;
import apis.dom.types;

import ext.assertion;
import ext.functional;
import ext.ranges;
import ext.string;
import ext.vector;

import js.env.module_type;
import js.env.realms;
import js.env.slots;


auto performance_timeline::performance_observer::observe(
        detail::performance_observer_init_t&& options)
        -> void
{
    ACCESS_PIMPL;
    auto e = js::env::env::relevant(this);
    using enum dom::detail::dom_exception_error_t;
    using enum v8_primitive_error_t;

    // Cannot observe when the options contain "entryTypes" amd "types" keys, or multiple keys when the "entryType" key
    // is set. This is because either "types" and more options are required, or only "entryTypes".
    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&options] {return !options.contains(u"entryTypes") && !options.contains(u"types");},
            u8"The 'options' must contain an 'entryTypes' or 'type' value", e);

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&options] {return options.contains(u"entryTypes") && options.size() > 1;},
            u8"The 'options' mustn't contain any other values if 'entryTypes' are provided", e);

    // Undefined types and "entryTypes" mean that the type is MULTIPLE.
    if (d->observer_type == detail::performance_observer_type_t::UNDEFINED && options.contains(u"entryTypes"))
        d->observer_type = detail::performance_observer_type_t::MULTIPLE;

    // Undefined types and "types" mean that the type is SINGLE.
    if (d->observer_type == detail::performance_observer_type_t::UNDEFINED && options.contains(u"types"))
        d->observer_type = detail::performance_observer_type_t::SINGLE;

    // Throw erors for incompatible types - "entryTypes" and SINGLA, or "tpyes" and MULTIPLE.
    dom::detail::throw_v8_exception<INVALID_MODIFICATION_ERR>(
            [type = d->observer_type, &options] {return type == detail::performance_observer_type_t::SINGLE && options.contains(u"entryTypes");},
            u8"", e);

    dom::detail::throw_v8_exception<INVALID_MODIFICATION_ERR>(
            [type = d->observer_type, &options] {return type == detail::performance_observer_type_t::MULTIPLE && options.contains(u"type");},
            u8"", e);

    // Set the 'requires_dropped_entries' to True TODO : Why?
    d->requires_dropped_entries = true;

    // Run different steps based on whether the MULTIPLE or SINGLE type is being used TODO : Why?
    if (d->observer_type == detail::performance_observer_type_t::MULTIPLE)
    {
        // Get the entry types from the 'options' map (converted to the corect type), and only keep the types which are
        // supported (check thay the global object's [[FrozenArraySupportedEntryTypes]] contains the types). Return if
        // there are no valid types -- nothing to to.
        decltype(auto) entry_types = options[u"entryTypes"].to<ext::vector<ext::string>>();
        entry_types |= ranges::actions::filter(ext::bind_front(ranges::contains, js::env::get_slot(e, js::env::slots::FROZEN_ARRAY_SUPPORTED_ENTRY_TYPES)));
        return_if (entry_types.empty());

        // The 'registered' observers are the global object's [[ListOfRegisteredPerformanceObservers]] -- deference the
        // pointer-vector to a reference-vector.
        decltype(auto) registered = *js::env::get_slot(e, js::env::slots::LIST_OF_REGISTERED_PERFORMANCE_OBSERVERS) | ranges::views::transform(ext::underlying);

        // If any of the [observers in the 'registered' list]'s observer attribute is this PerformanceObserver, then
        // get the struct and set its 'options' to the options passed into this method.
        if (ranges::contains(registered | ranges::views::transform_to_attr(&detail::registered_performance_observer_t::observer), this))
        {
            auto registered_observer = **ranges::first_where(registered, [this](auto* registered_observer) {return registered_observer->observer == this;});
            registered_observer->options = std::move(options);
        }

        // Otherwise, create a new registered observer, set its 'observer' to this PerformanceObserver, and its
        // 'options' to the 'options' passed into this method
        else
        {
            auto registered_observer = std::make_unique<detail::registered_performance_observer_t>();
            registered_observer->observer = this;
            registered_observer->options = std::move(options);
            registered->emplace_back(std::move(registered_observer));
        }
    }

    else
    {
        ext::assert(d->observer_type == detail::performance_observer_type_t::SINGLE);
        decltype(auto) types = options["types"].to<ext::string>();
        return_if (!ranges::contains(js::env::get_slot(e, js::env::slots::FROZEN_ARRAY_SUPPORTED_ENTRY_TYPES), std::move(types)));

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

module;
#include "ext/macros.hpp"

#include <assert.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/algorithm/contains.hpp>


module apis.performance_timeline.performance_observer;
import apis.performance_timeline.performance_entry;
import apis.performance_timeline.types;

import apis.dom.detail;
import apis.dom.types;

import ext.core;

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

    // The 'registered' observers are the global object's [[ListOfRegisteredPerformanceObservers]] -- deference the
    // pointer-vector to a reference-vector.
    decltype(auto) registered = *js::env::get_slot(e, js::env::slots::LIST_OF_REGISTERED_PERFORMANCE_OBSERVERS) | ranges::views::transform(ext::underlying);

    // Run different steps based on whether the MULTIPLE or SINGLE type is being used. First is the MULTIPLE type.
    if (d->observer_type == detail::performance_observer_type_t::MULTIPLE)
    {
        // Get the entry types from the 'options' map (converted to the corect type), and only keep the types which are
        // supported (check thay the global object's [[FrozenArraySupportedEntryTypes]] contains the types). Return if
        // there are no valid types -- nothing to to.
        decltype(auto) entry_types = options[u"entryTypes"].to<ext::vector<ext::string>>();
        entry_types |= ranges::actions::filter(ext::bind_front(ranges::contains, js::env::get_slot(e, js::env::slots::FROZEN_ARRAY_SUPPORTED_ENTRY_TYPES)));
        return_if (entry_types.empty());

        // If any of the [observers in the 'registered' list]'s observer attribute is this PerformanceObserver, then
        // get the struct and set its 'options' to the options passed into this method.
        if (decltype(auto) obs = **ranges::first_where(registered, [this](auto* obs) {return obs->observer == this;}))
            obs->options = std::move(options);

        // Otherwise, none of the observer struct contians an internal PerformanceObserver which is this, so create a
        // new registered observer, set its 'observer' to this PerformanceObserver, and its 'options' to the 'options'
        // passed into this method.
        else
        {
            decltype(auto) new_obs = std::make_unique<detail::registered_performance_observer_t>();
            new_obs->observer = this;
            new_obs->options = {std::move(options)};
            registered->emplace_back(std::move(new_obs));
        }
    }

    // The steps for the SINGLE type.
    else
    {
        // Given that the type isn't MULTIPLE, assert that it is SINGLE (not UNDEFINED). Get the types from the options
        // (used multiple time), and return if the type isn't supported.
        ext::assert_(d->observer_type == detail::performance_observer_type_t::SINGLE);
        decltype(auto) types = options["types"].to<ext::string>();
        return_if (!ranges::contains(js::env::get_slot(e, js::env::slots::FROZEN_ARRAY_SUPPORTED_ENTRY_TYPES), types));

        // If any of the [observers in the 'registered' list]'s observer attribute is this PerformanceObserver, then run
        // 1 from 2 stpes. If there is an options dictionary that has the same "type" set, then replace those options
        // with the new 'options'. Othwerise, append the new 'options' to that observers 'options'
        if (decltype(auto) obs = **ranges::first_where(registered, [this](auto* obs) {return obs->observer == this;}))
        {
            if (decltype(auto) current_options = ranges::first_where(obs->options, [types](auto&& options) {return options[u"type"].to<ext::string>() == types;}))
                obs->options |= ranges::actions::replace(*current_options, std::move(options));
            else
                obs->options.emplace_back(std::move(options));
        }

        // Otherwise, none of the observer struct contians an internal PerformanceObserver which is this, so create a
        // new registered observer, set its 'observer' to this PerformanceObserver, and its 'options' to the 'options'
        // passed into this method.
        else
        {
            decltype(auto) new_obs = std::make_unique<detail::registered_performance_observer_t>();
            new_obs->observer = this;
            new_obs->options = {std::move(options)};
            registered->emplace_back(std::move(new_obs));
        }

        // Support for the "buffered" option
        if (options[u"buffered"].to<ext::boolean>())
        {
            // Get the global objects [[PerformanceEntryBufferMap]], and its corresponsing value to the 'option's "type"
            // key. For all the entries that should be added, emplace them into the private class's 'observer_buffer'.
            decltype(auto) buffer_map = *js::env::get_slot(e, js::env::slots::PERFORMANCE_ENTRY_BUFFER_MAP);
            decltype(auto) tuple = buffer_map[options[u"type"].to<ext::string>()];
            tuple->performance_entry_buffer
                    | ranges::views::filter(ext::bind_back(detail::show_add_entry, options))
                    | ranges::views::for_each([d](auto* entry) {d->observer_buffer.emplace_back(entry);});

            // Queue a performance observer task
            detail::queue_performance_observer_task(e);
        }
    }
}


auto performance_timeline::performance_observer::disconnect()
        -> void
{
    auto e = js::env::env::relevant(this);

    // Remove the registered observer from the global object's [[ListOfRegisteredPerforanceObservers] whose 'observer'
    // is this. Move the unique_ptr<T> out the list (not owned by it any more, and at the end of the moethod the pointer]
    // will be cleared by automatic memory management.
    decltype(auto) registered = *js::env::get_slot(e, js::env::slots::LIST_OF_REGISTERED_PERFORMANCE_OBSERVERS);
    decltype(auto) obs = std::move(*ranges::first_where(registered, [this](auto&& obs) {return obs->observer.get() == this;}));
    registered |= ranges::actions::remove(std::move(obs));

    // Clear the private class's 'observer_buffer' and 'options' from the corresposning registered performance observer.
    ACCESS_PIMPL;
    d->observer_buffer.clear();
    obs->options.clear();

}


auto performance_timeline::performance_observer::take_records()
        -> ext::vector<performance_entry*>
{
    ACCESS_PIMPL;
    decltype(auto) current_records = std::move(d->observer_buffer);
    d->observer_buffer = {};
    return std::move(current_records) | ranges::views::transform(ext::underlying) | ranges::to_vector;
}


auto performance_timeline::performance_observer::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .ctor<detail::performance_observer_callback_t&&>()
        .function("observer", &performance_observer_callback_t::observer)
        .function("disconnect", &performance_observer_callback_t::disconnect)
        .function("takeRecords", &performance_observer_callback_t::take_records)
        .property("supportedEntryTypes", &performance_observer_callback_t::::get_supported_types)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

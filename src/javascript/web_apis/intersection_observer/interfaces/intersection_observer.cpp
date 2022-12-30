module;
#include "ext/macros.hpp"

#include <range/v3/action/remove.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/action/transform.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/view/for_each.hpp>
#include <swl/variant.hpp>


module apis.intersection_observer.intersection_observer;
import apis.intersection_observer.detail;
import apis.intersection_observer.types;

import apis.dom.element;
import apis.dom.node;
import apis.dom.detail;
import apis.dom.types;

import ext.core;
import js.env.module_type;
import js.env.realms;


intersection_observer::intersection_observer::intersection_observer(
        intersection_observer_callback_t&& callback,
        intersection_observer_init_t&& options)
{
    INIT_PIMPL; ACCESS_PIMPL;
    using enum v8_primitive_error_t;
    auto e = js::env::env::relevant(this);

    // Try to parse the "rootMargin" option (converted to a string) from the 'options' dictionary. The result is an
    // optional list of strings, with no value indicating a failure in the parsing. If there was a parsing failure, then
    // throw a JavaScript syntax error.
    auto parsed_root_margin = d->parse_root_margin(options.try_emplace(u"rootMargin").first->second.to<ext::string>());
    dom::detail::throw_v8_exception<V8_SYNTAX_ERROR>(
            [has_value = parsed_root_margin.has_value()] {return !has_value;},
            u8"Error parsing the 'rootMargin' option", e);

    // Get the "thresholds" (converted to a list of doubles), and throw a JavaScript RangeError if any of the threshold
    // values are less than 0.0 or greater than 1.0 (the threshold values must confirm to this range).
    auto parsed_thresholds = options.try_emplace(u"threshold").first->second.to<ext::vector<ext::number<double>>>();
    dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
            [&parsed_thresholds] {return ranges::any_of(parsed_thresholds, [](auto&& value) {return value < 0.0 || value > 1.0;});},
            u8"All values in the 'threshold' option must conform to [0.0 <= v <= 1.0]", e);

    // Sort the 'parsed_thresholds' into ascending order.
    // TODO: this shouldn't happen if the range is empty
    parsed_thresholds |= ranges::actions::sort(&ext::cmp::lt);

    // Set the callback and root margin slots to the parsed / verified option values, and set the 'thresholds' property
    // to the 'parsed_thresholds' converted to a list if not empty, otherwise {0.0}
    d->callback = std::move(callback);
    d->root = options[u"root"].to<dom::node*>();
    d->root_margin = *parsed_root_margin;
    d->thresholds = parsed_thresholds.empty() ? parsed_thresholds : decltype(d->thresholds){0.0};
}


auto intersection_observer::intersection_observer::observe(dom::element* target) -> void
{
    detail::observe_target_element(this, target);
}


auto intersection_observer::intersection_observer::unobserve(dom::element* target) -> void
{
    detail::unobserve_target_element(this, target);
}


auto intersection_observer::intersection_observer::disconnect() -> void
{
    ACCESS_PIMPL;

    // To disconnect this IntersectionObserver, unobserve every Element in the [[ObservationTargets]] slot.
    for (decltype(auto) target: d->observation_targets)
    {
        target->d_func()->registered_observer_list
                |= ranges::actions::transform(&detail::intersection_observer_registration_t::observer)
                | ranges::actions::remove(this, &ext::underlying);

        d->observation_targets |= ranges::actions::remove(target);
    }
}


auto intersection_observer::intersection_observer::take_records() -> ext::vector<intersection_observer_entry*>
{
    ACCESS_PIMPL;

    // To take the records, return a copy of the [[QueuedEntries]] slot, and clear the [[QueuedEntries]] slot
    auto queue = std::move(d->queued_entries);
    d->queued_entries = {};
    return std::move(queue);
}


auto intersection_observer::intersection_observer::get_root() const -> detail::document_or_element_t
{
    ACCESS_PIMPL;
    return ext::visit([]<typename T>(auto&& node) {dynamic_cast<T*>(node);}, detail::document_or_element_t());
}


auto intersection_observer::intersection_observer::get_root_margin() const -> ext::string
{
    ACCESS_PIMPL;
    return d->root_margin; // TODO : serialize
}


auto intersection_observer::intersection_observer::get_thresholds() const -> ext::span<ext::number<double>>
{
    ACCESS_PIMPL;
    return d->thresholds;
}


auto intersection_observer::intersection_observer::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .ctor<intersection_observer_callback_t&&, intersection_observer_init_t&&>()
        .function("observe", &intersection_observer::observe)
        .function("unobserve", &intersection_observer::unobserve)
        .function("disconnect", &intersection_observer::disconnect)
        .function("takeRecords", &intersection_observer::take_records)
        .property("root", &intersection_observer::get_root)
        .property("rootMargin", &intersection_observer::get_root_margin)
        .property("thresholds", &intersection_observer::get_thresholds)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

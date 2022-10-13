#include "intersection_observer.hpp"
#include "intersection_observer_private.hpp"

#include INCLUDE_INNER_TYPES(dom)

#include "ext/assertion.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"
#include "intersection_observer/detail/algorithm_internals.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/action/push_front.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/action/unique.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/view/for_each.hpp>


intersection_observer::intersection_observer::intersection_observer(
        detail::intersection_observer_callback_t&& callback,
        detail::intersection_observer_init_t&& options)
{
    INIT_PIMPL(intersection_observer);

    // Try to parse the "rootMargin" option (converted to a string) from the 'options' dictionary. The result is an
    // optional list of strings, with no value indicating a failure in the parsing. If there was a parsing failure, then
    // throw a JavaScript syntax error.
    auto parsed_root_margin = detail::parse_root_margin(options.try_emplace("rootMargin").first->second.to<ext::string>());
    dom::detail::throw_v8_exception<V8_SYNTAX_ERROR>(
            [has_value = parsed_root_margin.has_value()] {return !has_value;},
            "Error parsing the 'rootMargin' option");

    // Get the "thresholds" (converted to a list of doubles), and throw a JavaScript RangeError if any of the threshold
    // values are less than 0.0 or greater than 1.0 (the threshold values must confirm to this range).
    auto parsed_thresholds = options.try_emplace("threshold").first->second.to<ext::vector<ext::number<double>>>();
    dom::detail::throw_v8_exception<V8_RANGE_ERROR>(
            [&parsed_thresholds] {return ranges::any_of(parsed_thresholds, [](auto&& value) {return value < 0.0 || value > 1.0;});},
            "All values in the 'threshold' option must conform to [0.0 <= v <= 1.0]");

    // Sort the 'parsed_thresholds' into ascending order.
    // TODO: this shouldn't happen if the range is empty
    parsed_thresholds |= ranges::actions::sort(ext::cmp::lt{});

    // Set the callback and root margin slots to the parsed / verified option values, and set the 'thresholds' property
    // to the 'parsed_thresholds' converted to a list if not empty, otherwise {0.0}
    ACCESS_PIMPL(intersection_observer);
    d->callback = std::move(callback);
    d->root = options.try_emplace("root", nullptr).first->second.to<dom::nodes::node*>();
    d->root_margin = *parsed_root_margin;
    d->thresholds = parsed_thresholds.empty() ? parsed_thresholds : decltype(d->thresholds){0.0};
}


auto intersection_observer::intersection_observer::observe(
        dom::nodes::element* target)
        -> void
{
    ACCESS_PIMPL(intersection_observer);

    // Cannot re-observe an Element that is being observed already, so return early if the 'target' is already being
    // observed -- this is determined by checking if the 'target' is contained in the [[ObservationTargets]] slot.
    return_if (ranges::contains(d->observation_targets, target));

    // Create the 'intersection_observer_registration' struct, setting the 'observer' to 'this', and other attributes
    // that act as defaults to start the observing. Add the registration to the 'target's
    // [[RegistrationIntersectionObservers]], and add the 'target' to this IntersectionObserver's [[ObservationTargets]]
    // slot.
    auto intersection_observer_registration = std::make_unique<detail::intersection_observer_registration_t>();

    intersection_observer_registration->observer = this;
    intersection_observer_registration->previous_threshold_index = -1;
    intersection_observer_registration->previous_is_intersecting = false;
    target->d_func()->registration_intersection_observers.push_back(std::move(intersection_observer_registration));
    d->observation_targets.push_back(target);
}


auto intersection_observer::intersection_observer::unobserve(
        dom::nodes::element* target)
        -> void
{
    ACCESS_PIMPL(intersection_observer);

    // Cannot unobserve a null target, so return early
    return_if (!target);

    // Remove the registration from the 'target's [[RegistrationIntersectionObservers]] slot, and remove the 'target'
    // from this IntersectionObserver's [[ObservationTargets]] slot.
    target->d_func()->registration_intersection_observers
            |= ranges::actions::remove_if([this](auto&& unique_registration) {return unique_registration->observer == this;});
    d->observation_targets |= ranges::actions::remove(target);
}


auto intersection_observer::intersection_observer::disconnect()
        -> void
{
    ACCESS_PIMPL(intersection_observer);

    // To disconnect this IntersectionObserver, unobserve every Element in the [[ObservationTargets]] slot.
    d->observation_targets | ranges::views::for_each(&intersection_observer::unobserve);
}


auto intersection_observer::intersection_observer::take_records()
        -> ext::vector<intersection_observer_entry*>
{
    ACCESS_PIMPL(intersection_observer);

    // To take the records, return a copy of the [[QueuedEntries]] slot, and clear the [[QueuedEntries]] slot
    auto queue = std::move(d->queued_entries);
    d->queued_entries = {};
    return std::move(queue);
}


auto intersection_observer::intersection_observer::get_root() const -> detail::document_or_element_t
{
    ACCESS_PIMPL(const intersection_observer);
    return ext::visit([d]<typename T>(T*) -> detail::document_or_element_t {return dynamic_cast<T*>(d->root);}, detail::document_or_element_t{});
}


auto intersection_observer::intersection_observer::get_root_margin() const -> ext::string
{
    ACCESS_PIMPL(const intersection_observer);
    return d->root_margin; // TODO : serialize
}


auto intersection_observer::intersection_observer::get_thresholds() const -> ext::vector_span<ext::number<double>>
{
    ACCESS_PIMPL(const intersection_observer);
    return d->thresholds;
}


auto intersection_observer::intersection_observer::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<intersection_observer>{isolate}
        .ctor<detail::intersection_observer_callback_t&&, detail::intersection_observer_init_t&&>()
        .function("observe", &intersection_observer::observe)
        .function("unobserve", &intersection_observer::unobserve)
        .function("disconnect", &intersection_observer::disconnect)
        .function("takeRecords", &intersection_observer::take_records)
        .property("root", &intersection_observer::get_root)
        .property("rootMargin", &intersection_observer::get_root_margin)
        .property("thresholds", &intersection_observer::get_thresholds)
        .auto_wrap_objects();

    return std::move(conversion);
}

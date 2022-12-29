module;
#include "ext/macros/language_shorthand.hpp"
#include <range/v3/algorithm/contains.hpp>


module apis.intersection_observer.detail;
import apis.intersection_observer.intersection_observer;
import apis.intersection_observer.intersection_observer_private;
import apis.intersection_observer.types;

import apis.dom.element;
import apis.dom.element_private;


auto intersection_observer::detail::observe_target_element(
        intersection_observer* observer,
        dom::element* target) -> void
{
    // Cannot re-observe an Element that is being observed already, so return early if the 'target' is already being
    // observed -- this is determined by checking if the 'target' is contained in the [[ObservationTargets]] slot.
    return_if (ranges::contains(observer->d_func()->observation_targets, target));

    // Create the 'intersection_observer_registration' struct.
    auto intersection_observer_registration = std::make_unique<detail::intersection_observer_registration_t>();

    // Set the 'observer' to 'this', and other attributes that act as defaults to start the observing. Add the
    // registration to the 'target's [[RegistrationIntersectionObservers]], and add the 'target' to the 'observer's
    // IntersectionObserver's [[ObservationTargets]] slot.
    intersection_observer_registration->observer = observer;
    intersection_observer_registration->previous_threshold_index = -1;
    intersection_observer_registration->previous_is_intersecting = false;
    target->d_func()->registration_intersection_observers.push_back(std::move(intersection_observer_registration));
    observer->d_func()->observation_targets.push_back(target);
}


intersection_observer::detail::unobserve_target_element(
        intersection_observer* observer,
        dom::element* target)
        -> void
{
    // Cannot unobserve a null target, so return early
    return_if (!target);

    // Remove the registration from the 'target's [[RegistrationIntersectionObservers]] slot, and remove the 'target'
    // from this IntersectionObserver's [[ObservationTargets]] slot.
    target->d_func()->registration_intersection_observers
            |= ranges::actions::remove_if([this](auto&& r) {return r->observer == this;});

    observer->d_func()->observation_targets
            |= ranges::actions::remove(target);
}


auto intersection_observer::detail::intersection_root(
        intersection_observer* observer)
        -> dom::nodes::node*
{
    // The intersection root of an IntersectionObserver is the explicit root is available, otherwise the implicit root
    // -- so the 'root' attribute  if it isn't nullptr, otherwise the implied root.
    decltype(auto) root = ext::visit([](auto* node) {return dynamic_cast<dom::nodes::node*>(node);}, observer->d_func()->root.get());
    return root ?: implicit_root(observer);
}


auto intersection_observer::detail::implicit_root(
        intersection_observer* observer)
        -> dom::nodes::node*
{
    // Get the current javascript context, and return the document of the current Window global object as the implicit
    // root.
    auto e = js::env::env::current();
    decltype(auto) window = e.cpp.global<dom::nodes::window*>();
    decltype(auto) implicit_root = window->d_func()->document.get();

    return implicit_root;
}


auto intersection_observer::detail::is_explicit_root_observer(
        intersection_observer* observer)
        -> ext::boolean
{
    // An explicit root observer is an IntersectionObserver whose 'root' attribute isn't nullptr.
    decltype(auto) root = ext::visit([](auto* node) {return dynamic_cast<dom::nodes::node*>(node);}, observer->d_func()->root.get());
    return root != nullptr;
}


auto intersection_observer::detail::is_implicit_root_observer(
        intersection_observer* observer) -> ext::boolean
{
    // An explicit root observer is an IntersectionObserver whose 'root' attribute is nullptr.
    decltype(auto) root = ext::visit([](auto* node) {return dynamic_cast<dom::nodes::node*>(node);}, observer->d_func()->root.get());
    return root == nullptr;
}


auto intersection_observer::detail::parse_root_margin(
        ext::string_view margin_string)
        -> ext::optional<ext::array<ext::number<int>, 4>>
{
    auto tokens = ext::vector<ext::string>{}; // TODO: css::detail::parse_list_of_component_values(margin_string);
    tokens |= ranges::actions::remove(u" ");

    auto validity_check = []<typename T>(T&& value) {return css::detail::is_absolute_length_dimension(std::forward<T>(value) || css::detail::is_percentage_token(std::forward<T>(value)));};
    return_if (tokens.size() > 4) ext::nullopt;
    return_if (ranges::any_of(tokens, validity_check)) ext::nullopt;

    if (tokens.empty()) tokens.emplace_back(u"0px");

    // TODO
    auto parsed = tokens
            | ranges::views::replace_if(css::detail::is_absolute_length_dimension, 0)
            | ranges::views::replace_if(css::detail::is_percentage_token, 0);

    using arr = ext::array<ext::number<int>, 4>;
    return_if (parsed.size() == 1) parsed | ranges::views::cycle | ranges::views::take(4) | ranges::to<arr>;
    return_if (parsed.size() == 2) parsed | ranges::views::cycle | ranges::views::take(4) | ranges::to<arr>;
    return_if (parsed.size() == 3) parsed | ranges::views::take(2) | ranges::views::cycle | ranges::views::take(4) | ranges::to<arr>; // TODO : {1, 2, 3} -> {1, 2, 1, 2}, should be {1, 2, 3, 2}
    return_if (parsed.size() == 4) parsed | ranges::to<arr>;
}


auto intersection_observer::detail::queue_intersection_observer_task(
        dom::nodes::document* document)
        -> void
{
    return_if (document->m_intersection_observer_task_queued);
    document->m_intersection_observer_task_queued = true;
    dom::detail::queue_task(html::detail::intersection_observer_task_source,
            [document]
            {notify_intersection_observers(document);});
}


auto intersection_observer::detail::notify_intersection_observers(
        dom::nodes::document* document)
        -> void
{
    document->m_intersection_observer_task_queued = false;
    auto notify_list = ext::vector_span<intersection_observer*>{}; // TODO: IntersectionObservers whose root is 'document'

    for (decltype(auto) observer: notify_list)
    {
        continue_if (observer->d_func()->queued_entries().empty());

        decltype(auto) queue = observer->take_records();
        decltype(auto) callback = observer->d_func()->callback();

        JS_EXCEPTION_HANDLER;
        callback(queue, observer);

        if (JS_EXCEPTION_HAS_THROWN)
            console::reporting::report_exception(JS_EXCEPTION_MESSAGE);
    }
}

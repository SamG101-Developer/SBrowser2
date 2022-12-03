#include "algorithm_internals.hpp"



#include "dom/detail/observer_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/element_private.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"

#include "hr_time/performance.hpp"
#include "html/detail/task_internals.hpp"

#include "intersection_observer/intersection_observer.hpp"
#include "intersection_observer/intersection_observer_private.hpp"
#include "intersection_observer/intersection_observer_entry.hpp"
#include "intersection_observer/intersection_observer_entry_private.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/action/remove.hpp>
#include <range/v3/view/cycle.hpp>
#include <range/v3/view/replace_if.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/to_container.hpp>
#include <v8pp/convert.hpp>


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

#include "algorithm_internals.hpp"

#include "dom/nodes/document.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/window.hpp"

#include "intersection_observer/intersection_observer.hpp"

#include <v8pp/convert.hpp>


auto intersection_observer::detail::intersection_root(
        intersection_observer* observer)
        -> dom::nodes::node*
{
    // The intersection root of an IntersctionObserver is the explicit root is available, otherwise the implicit root --
    // so the 'root' attribute  if it isn't nullptr, otherwise the implied root.
    decltype(auto) root = ext::visit([](auto* node) {return dynamic_cast<dom::nodes::node*>(node);}, observer->root());
    return root ?: implicit_root(observer);
}


auto intersection_observer::detail::implicit_root(
        intersection_observer* observer)
        -> dom::nodes::node*
{
    // Get the current javascript context, and return the document of the current Window global object as the implicit
    // root.
    JS_REALM_GET_CURRENT; // TODO
    decltype(auto) window = v8pp::from_v8<dom::nodes::window*>(current_agent, current_global_object);
    decltype(auto) implicit_root = window->document();

    return implicit_root;
}


auto intersection_observer::detail::is_explicit_root_observer(
        intersection_observer* observer)
        -> ext::boolean
{
    // An explicit root observer is an IntersectionObserver whose 'root' attribute isn't nullptr.
    decltype(auto) root = ext::visit([](auto* node) {return dynamic_cast<dom::nodes::node*>(node);}, observer->root());
    return root != nullptr;
}


auto intersection_observer::detail::is_implicit_root_observer(
        intersection_observer* observer) -> ext::boolean
{
    // An explicit root observer is an IntersectionObserver whose 'root' attribute is nullptr.
    decltype(auto) root = ext::visit([](auto* node) {return dynamic_cast<dom::nodes::node*>(node);}, observer->root());
    return root == nullptr;
}

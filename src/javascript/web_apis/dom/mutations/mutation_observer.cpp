#include "mutation_observer.hpp"
#include "ext/functional.hpp"
#include "mutation_observer_private.hpp"

#include "ext/ranges.hpp"

#include "javascript/environment/isolate_data_slots.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/mutation_internals.hpp"
#include "dom/nodes/node.hpp"
#include "dom/nodes/node_private.hpp"
#include "dom/nodes/window.hpp"

#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/transform.hpp>


dom::mutations::mutation_observer::mutation_observer(detail::mutation_callback_t&& callback)
{
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) window = v8pp::from_v8<nodes::window*>(this_relevant_agent, this_relevant_global_object);
    decltype(auto) agent_mutation_observers = this_relevant_agent->GetData(javascript::isolate_data_slots::mutation_observers);
    static_cast<ext::vector<std::unique_ptr<mutation_observer>>*>(agent_mutation_observers)->emplace_back(this);

    INIT_PIMPL(mutation_observer);
    ACCESS_PIMPL(mutation_observer);
    d->callback = std::move(callback);
}


auto dom::mutations::mutation_observer::observe(
        nodes::node* target,
        detail::mutation_observer_init_t&& options) -> void
{
    ACCESS_PIMPL(mutation_observer);
    using enum v8_primitive_error_t;

    // If there is an old attribute value and an attribute filter, then set the "attributes" option to true, as it is
    // the attribute that must be being observerd (implied by giving an old value and filter). The check on the
    // "attributes" option is for micro-optimization.
    if (options.contains(u8"attributeOldValue") && options.contains(u8"attributeFilter") && !options.contains(u8"attributes"))
        options.insert_or_assign(u8"attributes", ext::boolean::TRUE_());

    // If there is an olf character data value, the set the "characterData" option to true, as it is the character data
    // that must be being observed (implied by giving an old value). The check on the "charcaterData" option is for
    // micro-optimization.
    if (options.contains(u8"characterOldDataValue") && !options.contains(u8"characterData"))
        options.insert_or_assign(u8"characterData", ext::boolean::TRUE_());

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&options] {!options.contains(u8"childList") && !options.contains(u8"attributes") && !options.contains(u8"characterData");},
            u8"Either the childList, attributes of characterData must be observed");


    auto node_removal = [](detail::registered_observer_t* registered, nodes::node* node)
            {
                node->d_func()->registered_observer_list
                        |= ranges::actions::remove_if([registered](auto* check) {return dynamic_cast<detail::transient_registered_observer_t*>(check)->source == registered;});
            };

    using enum ranges::filter_compare_t;
    target->d_func()->registered_observer_list
            | ranges::views::transform(&std::unique_ptr<detail::registered_observer_t>::get)
            | ranges::views::filter_eq<EQ>(&detail::registered_observer_t::observer, this, ext::identity{})
            | ranges::views::for_each([d, &node_removal](detail::registered_observer_t* registered) {d->node_list | ranges::views::for_each(BIND_FRONT(node_removal, registered));})
            | ranges::views::for_each([options = std::move(options)](detail::registered_observer_t* registered) {registered->options = options;});

    target->d_func()->registered_observer_list
            | ranges::views::transform(&std::unique_ptr<detail::registered_observer_t>::get)
            | ranges::views::filter_eq<NE>(&detail::registered_observer_t::observer, this, ext::identity{})
            | ranges::views::for_each(/* TODO */);
}


auto dom::mutations::mutation_observer::disconnect() -> void
{
    ACCESS_PIMPL(mutation_observer);
}

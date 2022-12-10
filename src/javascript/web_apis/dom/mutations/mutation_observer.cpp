module;
#include "ext/macros/pimpl.hpp"
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/action/remove_if.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/view/transform.hpp>


module apis.dom.mutation_observer;
import apis.dom.mutation_observer_private;
import apis.dom.node;
import apis.dom.node_private;

import ext.hashing;

import js.env.realms;
import js.env.slots;


dom::mutation_observer::mutation_observer(mutation_callback_t&& callback)
{
    auto e = js::env::env::relevant(this);
    decltype(auto) mutation_observers = js::env::get_slot(e, js::env::slots::MUTATION_OBSERVERS);
    mutation_observers.emplace_back(this);

    INIT_PIMPL; ACCESS_PIMPL;
    d->callback = std::move(callback);
}


auto dom::mutation_observer::observe(node* target, mutation_observer_init_t&& options) -> void
{
    ACCESS_PIMPL;
    using enum v8_primitive_error_t;

    // If there is an old attribute value and an attribute filter, then set the "attributes" option to true, as it is
    // the attribute that must be being observerd (implied by giving an old value and filter). The check on the
    // "attributes" option is for micro-optimization.
    if (options.contains(u"attributeOldValue") && options.contains(u"attributeFilter") && !options.contains(u"attributes"))
        options.insert_or_assign(u"attributes", true);

    // If there is an olf character data value, the set the "characterData" option to true, as it is the character data
    // that must be being observed (implied by giving an old value). The check on the "charcaterData" option is for
    // micro-optimization.
    if (options.contains(u"characterOldDataValue") && !options.contains(u"characterData"))
        options.insert_or_assign(u"characterData", true);

    detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&options] {!options.contains(u"childList") && !options.contains(u"attributes") && !options.contains(u"characterData");},
            u8"Either the childList, attributes of characterData must be observed");


    auto node_removal = [](registered_observer_t& registered, node* node)
            {
                node->d_func()->registered_observer_list
                        |= ranges::actions::remove_if([registered](auto* check) {return dynamic_cast<detail::transient_registered_observer_t*>(check)->source == registered;});
            };

    using enum ranges::filter_compare_t;
    target->d_func()->registered_observer_list
            | ranges::views::transform(&std::unique_ptr<detail::registered_observer_t>::get)
            | ranges::views::filter_eq<EQ>(&detail::registered_observer_t::observer, this, ext::identity)
            | ranges::views::for_each([d, &node_removal](detail::registered_observer_t* registered) {d->node_list | ranges::views::for_each(BIND_FRONT(node_removal, registered));})
            | ranges::views::for_each([options = std::move(options)](detail::registered_observer_t* registered) {registered->options = options;});

    target->d_func()->registered_observer_list
            | ranges::views::transform(&std::unique_ptr<detail::registered_observer_t>::get)
            | ranges::views::filter_eq<NE>(&detail::registered_observer_t::observer, this, ext::identity)
            | ranges::views::for_each(/* TODO */);
}


auto dom::mutation_observer::disconnect() -> void
{
    ACCESS_PIMPL(mutation_observer);
//    d->node_list
//            |= ranges::actions::transform(&nodes::node_private::registered_observer_list, &dom::nodes::node::d_func)
//            | ranges::actions::transform(&std::unique_ptr<detail::registered_observer_t>::get)
//            | ranges::actions::transform(&detail::registered_observer_t::observer)
//            | ranges::actions::remove_if(BIND_FRONT(ext::cmp::eq, this));

    d->record_queue.clear();
    d->node_list
            |= ranges::actions::transform([](auto* node) {return &node->d_func()->registered_observer_list;})
            |  ranges::actions::transform([](auto* registered_list) {return *registered_list | ranges::transform(&detail::registered_observer_t::observer);})
            |  ranges::actions::remove_if(BIND_FRONT(ext::cmp::eq, this));
}


auto dom::mutation_observer::take_records() -> ext::vector<mutation_record*>
{
    ACCESS_PIMPL(mutation_observer); // TODO -> unique_ptr
    decltype(auto) current_records = std::move(d->record_queue);
    d->record_queue = {};
    return {std::make_move_iterator(&current_records.front()), std::make_move_iterator(&current_records.back())};
}


auto dom::mutation_observer::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .ctor<detail::mutation_callback_t&&>()
        .function("observe", &mutation_observer::observe)
        .function("disconnect", &mutation_observer::disconnect)
        .function("takeRecords", &mutation_observer::take_records)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

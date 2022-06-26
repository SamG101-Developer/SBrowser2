#include "event_target.hpp"

#include <web_apis/dom/detail/exception_internals.hpp>
#include <web_apis/dom/detail/event_internals.hpp>
#include <web_apis/dom/events/event.hpp>


auto dom::nodes::event_target::add_event_listener(
        ext::string&& type,
        event_listener_callback_t&& callback,
        ext::string_any_map& options)
        -> void
{
    // create an event listener that is the flattened options, and insert the callback and type
    auto event_listener = detail::event_internals::flatten_more(options);
    event_listener.insert_or_assign("callback", std::forward<event_listener_callback_t>(callback));
    event_listener.insert_or_assign("type"    , std::forward<ext::string              >(type    ));

    // add the event listener to the event target by calling the add_event_listener helper method
    detail::event_internals::add_event_listener(this, event_listener);
}


auto dom::nodes::event_target::remove_event_listener(
        ext::string&& type,
        event_listener_callback_t&& callback,
        ext::string_any_map& options)
        -> void
{
    // create a dummy event listener that is the flattened options, and insert the callback and type
    auto event_listener = detail::event_internals::flatten_more(options);
    event_listener.insert_or_assign("callback", std::move(callback));
    event_listener.insert_or_assign("type", type);

    // remove the event listener from the event target by  calling the remove_event_listener helper method
    detail::event_internals::remove_event_listener(this, event_listener);
}


auto dom::nodes::event_target::dispatch_event(
        events::event* event)
        -> ext::boolean
{
    // if the dispatch is already set or the initialized flag isn't set, then throw an invalid state error
    detail::exception_internals::throw_v8_exception_formatted<INVALID_STATE_ERR>(
            [event] {return event->m_dispatch_flag || not event->m_initialized_flag;},
            "Event must be initialized and not dispatched in order be dispatched");

    // set the event trusted to false (manual dispatch), and dispatch the event through the tree
    event->is_trusted = ext::boolean::FALSE();
    return detail::event_internals::dispatch(event, this);
}


auto dom::nodes::event_target::get_the_parent(
        events::event* event)
        -> event_target*
{
    // default behaviour for getting the parent in event traversal is that there is no parent
    return nullptr;
}


auto dom::nodes::event_target::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<event_target>{isolate}
            .ctor<>()
            .inherit<web_apis::dom_object>()
            .function("addEventListener", &event_target::add_event_listener)
            .function("removeEventListener", &event_target::remove_event_listener)
            .function("dispatchEvent", &event_target::dispatch_event)
            .auto_wrap_objects();
}

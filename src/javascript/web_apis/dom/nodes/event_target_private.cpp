module apis.dom.event_target_private;

import apis.dom.event;
import ext.any;
import ext.boolean;
import ext.concepts;
import ext.map;
import ext.string;


auto dom::event_target_private::remove_all_event_listeners() -> void
{
    // Iterate over the event listeners of the 'event_target', and remove each listener from the 'event_target' using
    // the predefined removal algorithm defined in the EventTarget class.
    for (decltype(auto) existing_listener: event_listeners)
        remove_event_listener(
                existing_listener.at(u"type").to<ext::string>(),
                existing_listener.at(u"callback").to<detail::event_listener_callback_t>(),
                std::move(existing_listener));
}


template <ext::inherit<dom::event> T>
auto dom::event_target_private::fire_event(ext::string&& e, ext::map<ext::string, ext::any>&& init) -> ext::boolean
{
    using namespace std::string_literals;

    string_switch(e)
    {
        string_case(u"pointerover"):
        string_case(u"pointerdown"):
        string_case(u"pointermove"):
        string_case(u"pointerup"):
        string_case(u"pointerout"):
        init.template insert_or_assign(u"bubbles", true);
        init.template insert_or_assign(u"cancelable", true);
        break;

        string_case(u"pointerenter"):
        string_case(u"pointerleave"):
        string_case(u"load"):
        string_case(u"unload"):
        string_case(u"abort"):
        string_case(u"error"):
        init.template insert_or_assign(u"bubbles", false);
        init.template insert_or_assign(u"cancelable", false);
        break;

        string_case(u"pointerrawupdate"):
        string_case(u"pointercancel"):
        string_case(u"gotpointercapture"):
        string_case(u"lostpointercapture"):
        string_case(u"select"):
        string_case(u"animationstart"):
        string_case(u"animationend"):
        string_case(u"animationiteration"):
        string_case(u"animationcancelable"):
        init.template insert_or_assign(u"bubbles", true);
        init.template insert_or_assign(u"cancelable", false);
        break;

        string_case(u"touchcancel"):
        init.template insert_or_assign(u"cancelable", false);
        init.template insert_or_assign(u"bubbles", true);
        init.template insert_or_assign(u"composed", true);
        break;

        string_case(u"blur"):
        string_case(u"focus"):
        string_case(u"mouseenter"):
        string_case(u"mouseleave"):
        init.template insert_or_assign(u"bubbles", false);
        init.template insert_or_assign(u"cancelable", false);
        init.template insert_or_assign(u"composed", true);
        break;

        string_case(u"focusin"):
        string_case(u"focusout"):
        string_case(u"input"):
        string_case(u"compositionupdate"):
        string_case(u"compositionend"):
        init.template insert_or_assign(u"bubbles", true);
        init.template insert_or_assign(u"cancelable", false);
        init.template insert_or_assign(u"composed", true);
        break;

        string_case(u"auxclick"):
        string_case(u"click"):
        string_case(u"contextmenu"):
        string_case(u"dblclick"):
        string_case(u"mousedown"):
        string_case(u"mousemove"):
        string_case(u"mouseout"):
        string_case(u"mouseover"):
        string_case(u"mouseup"):
        string_case(u"beforeinput"):
        string_case(u"keydown"):
        string_case(u"keyup"):
        string_case(u"compositionstart"):
        init.template insert_or_assign(u"bubbles", true);
        init.template insert_or_assign(u"cancelable", true);
        init.template insert_or_assign(u"composed", true);
        break;

        string_case(u"wheel"):
        string_case(u"touchstart"):
        string_case(u"touchend"):
        string_case(u"touchmove"):
        init.template insert_or_assign(u"bubbles", true);
        init.template insert_or_assign(u"composed", true);
        break;
    }

    if constexpr (type_is<T, indexed_db::events::idb_version_change_event>)
    {
        init.template insert_or_assign(u"bubbles", false);
        init.template insert_or_assign(u"cancelable", false);
    }

    // create a new event of type T, setting the event type and options, and then dispatch it to 'target'
    T event {std::move(e), std::move(init)};
    return dispatch(&event, target);
}


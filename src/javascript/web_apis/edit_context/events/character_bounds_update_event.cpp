#include "character_bounds_update_event.hpp"


edit_context::events::character_bounds_update_event::character_bounds_update_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : dom::events::event{std::move(event_type), std::move(event_init)}
{
    INIT_PIMPL(character_bounds_update_event);

    ACCESS_PIMPL(character_bounds_update_event);
    d->range_start = event_init[u"rangeStart"].to<decltype(d->range_start)>();
    d->range_end = event_init[u"rangeEnd"].to<decltype(d->range_end)>();
}


auto edit_context::events::character_bounds_update_event::get_range_start() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const character_bounds_update_event);
    return d->range_start;
}


auto edit_context::events::character_bounds_update_event::get_range_end() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const character_bounds_update_event);
    return d->range_end;
}


auto edit_context::events::character_bounds_update_event::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom::events::event>()
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .property("rangeStart", &character_bounds_update_event::get_range_start)
        .property("rangeEnd", &character_bounds_update_event::get_range_end)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

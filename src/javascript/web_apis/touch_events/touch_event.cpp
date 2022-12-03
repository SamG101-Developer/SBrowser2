#include "touch_event.hpp"
#include "touch_event_private.hpp"

#include "touch_events/touch.hpp"




touch_events::touch_event::touch_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : ui_events::mixins::modifier_event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(touch_event);

    ACCESS_PIMPL(touch_event);
    d->touches = event_init[u8"touches"].to<ext::vector<touch*>>() | ranges::views::transform_to_obj.CALL_TEMPLATE_LAMBDA<std::unique_ptr<touch>>();
    d->target_touches = event_init[u8"targetTouches"].to<ext::vector<touch*>>() | ranges::views::transform_to_obj.CALL_TEMPLATE_LAMBDA<std::unique_ptr<touch>>();
    d->changed_touches = event_init[u8"chabgedTouches"].to<ext::vector<touch*>>() | ranges::views::transform_to_obj.CALL_TEMPLATE_LAMBDA<std::unique_ptr<touch>>();
}


auto touch_events::touch_event::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<touch_event>{isolate}
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .inherit<ui_events::mixins::modifier_event>()
        .property("touches", &touch_event::get_touches)
        .property("targetTouches", &touch_event::get_target_touches)
        .property("changedTouches", &touch_event::get_changed_touches)
        .auto_wrap_objects();

    return std::move(conversion);
}

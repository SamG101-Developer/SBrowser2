#include "custom_event.hpp"
#include "custom_event_private.hpp"


dom::events::custom_event::custom_event(
        ext::string&& event_type,
        ext::map<ext::string, ext::any>&& event_init)
        : event(std::move(event_type), std::move(event_init))
{
    INIT_PIMPL(custom_event);
    d_func()->detail = 0;
}


auto dom::events::custom_event::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<custom_event>{isolate}
        .inherit<event>()
        .ctor<ext::string&&, ext::map<ext::string, ext::any>&&>()
        .property("detail", &custom_event::get_detail)
        .auto_wrap_objects();

    return std::move(conversion);
}

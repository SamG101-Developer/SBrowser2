#include "task_attribution_timing.hpp"


#include "html/detail/context_internals.hpp"
#include "longtasks/detail/processing_internals.hpp"

// TODO : v8 stuff in this file ???


auto longtasks::task_attribution_timing::get_container_type() const -> ext::string
{
    decltype(auto) container = detail::culprit_browsing_context_container(this);
    return container ? typeid(container).name() : u"window"; // TODO
}


auto longtasks::task_attribution_timing::get_container_name() const -> ext::string
{
    auto e = js::env::env::relevant(this);
    decltype(auto) container = detail::culprit_browsing_context_container(this);
    decltype(auto) v8_isolate = e.js.agent();

    auto v8_container = v8pp::to_v8(v8_isolate, container);
    auto v8_name = v8pp::to_v8(v8_isolate, u"name");
    return container ? v8pp::from_v8<ext::string>(v8_isolate, v8_container->Get(e.js.agent(), v8_name).ToLocalChecked()) : u"";
}


auto longtasks::task_attribution_timing::get_container_id() const -> ext::string
{
    auto e = js::env::env::relevant(this);
    decltype(auto) container = detail::culprit_browsing_context_container(this);
    decltype(auto) v8_isolate = e.js.agent();

    auto v8_container = v8pp::to_v8(v8_isolate, container);
    auto v8_name = v8pp::to_v8(v8_isolate, u"id");
    return container ? v8pp::from_v8<ext::string>(v8_isolate, v8_container->Get(e.js.agent(), v8_name).ToLocalChecked()) : u"";
}


auto longtasks::task_attribution_timing::get_container_src() const -> ext::string
{
    auto e = js::env::env::relevant(this);
    decltype(auto) container = detail::culprit_browsing_context_container(this);
    decltype(auto) v8_isolate = e.js.agent();

    auto v8_container = v8pp::to_v8(v8_isolate, container);
    auto v8_name = v8pp::to_v8(v8_isolate, u"src");
    return container ? v8pp::from_v8<ext::string>(v8_isolate, v8_container->Get(e.js.agent(), v8_name).ToLocalChecked()) : u"";
}

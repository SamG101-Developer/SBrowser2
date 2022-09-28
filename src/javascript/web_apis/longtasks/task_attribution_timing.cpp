#include "task_attribution_timing.hpp"

#include "dom/nodes/element.hpp"
#include "html/detail/context_internals.hpp"
#include "longtasks/detail/processing_internals.hpp"


auto longtasks::task_attribution_timing::get_container_type() const -> ext::string
{
    decltype(auto) container = detail::culprit_browsing_context_container(this);
    return container ? typeid(container).name() : "window"; // TODO
}


auto longtasks::task_attribution_timing::get_container_name() const -> ext::string
{
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) container = detail::culprit_browsing_context_container(this);
    decltype(auto) v8_isolate = this_relevant_agent;

    auto v8_container = v8pp::to_v8(v8_isolate, container);
    auto v8_name = v8pp::to_v8(v8_isolate, "name");
    return container ? v8pp::from_v8<ext::string>(v8_isolate, v8_container->Get(this_relevant_realm, v8_name).ToLocalChecked()) : "";
}


auto longtasks::task_attribution_timing::get_container_id() const -> ext::string
{
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) container = detail::culprit_browsing_context_container(this);
    decltype(auto) v8_isolate = this_relevant_agent;

    auto v8_container = v8pp::to_v8(v8_isolate, container);
    auto v8_name = v8pp::to_v8(v8_isolate, "id");
    return container ? v8pp::from_v8<ext::string>(v8_isolate, v8_container->Get(this_relevant_realm, v8_name).ToLocalChecked()) : "";
}


auto longtasks::task_attribution_timing::get_container_src() const -> ext::string
{
    JS_REALM_GET_RELEVANT(this);
    decltype(auto) container = detail::culprit_browsing_context_container(this);
    decltype(auto) v8_isolate = this_relevant_agent;

    auto v8_container = v8pp::to_v8(v8_isolate, container);
    auto v8_name = v8pp::to_v8(v8_isolate, "src");
    return container ? v8pp::from_v8<ext::string>(v8_isolate, v8_container->Get(this_relevant_realm, v8_name).ToLocalChecked()) : "";
}

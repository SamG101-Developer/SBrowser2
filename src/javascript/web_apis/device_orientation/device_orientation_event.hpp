#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_HPP

#include "dom/events/event.hpp"
namespace device_orientation {class device_orientation_event;}

#include "ext/promise.hpp"
#include "ext/boolean.hpp"
#include INCLUDE_INNER_TYPES(device_orientation)


class device_orientation::device_orientation_event
        : public dom::events::event
{
public constructors:
    DOM_CTORS(device_orientation_event);
    device_orientation_event() = default;
    device_orientation_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_methods:
    static auto request_permission() -> ext::promise<detail::permission_state_t>;

private js_properties:
    ext::property<ext::number<double>> alpha;
    ext::property<ext::number<double>> beta;
    ext::property<ext::number<double>> gamma;
    ext::property<ext::boolean> absolute;

public cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DEVICE_ORIENTATION_DEVICE_ORIENTATION_EVENT_HPP

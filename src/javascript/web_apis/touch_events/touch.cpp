#include "touch.hpp"
#include "touch_private.hpp"

#include "dom/nodes/event_target.hpp"


touch_events::touch::touch(
        detail::touch_init && options)
{
    INIT_PIMPL(touch);

    ACCESS_PIMPL(touch);
    d->identifier = options[u8"identifier"].to<decltype(d->identifier)>();
    d->target = options[u8"target"].to<decltype(d->target)::pointer>();

    d->client_x = options[u8"clientX"].to<decltype(d->client_x)>();
    d->client_y = options[u8"clientY"].to<decltype(d->client_y)>();
    d->screen_x = options[u8"screenX"].to<decltype(d->screen_x)>();
    d->screen_x = options[u8"screenY"].to<decltype(d->screen_y)>();
    d->page_x = options[u8"pageX"].to<decltype(d->page_x)>();
    d->page_x = options[u8"pageY"].to<decltype(d->page_y)>();
    d->radius_x = options[u8"radiusX"].to<decltype(d->radius_x)>();
    d->radius_x = options[u8"radiusY"].to<decltype(d->radius_y)>();

    d->rotation_angle = options[u8"rotationAngle"].to<decltype(d->rotation_angle)>();
    d->force = options[u8"force"].to<decltype(d->force)>();
    d->altitude_angle = options[u8"altitudeAngle"].to<decltype(d->altitude_angle)>();
    d->azimuth_angle = options[u8"azimuthAngle"].to<decltype(d->azimuth_angle)>();

    d->touch_type = options[u8"touchType"].to<decltype(d->touch_type)>(); // TODO : default to ...::DIRECT
}

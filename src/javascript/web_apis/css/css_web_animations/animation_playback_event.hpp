#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_PLAYBACK_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_PLAYBACK_EVENT_HPP

#include "dom/events/event.hpp"
namespace css::css_web_animations {class animation_playback_event;}


class css::css_web_animations::animation_playback_event
        : public dom::events::event
{
public constructors:
    animation_playback_event() = default;
    animation_playback_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});

public js_properties:
    ext::property<ext::number<double>> current_time;
    ext::property<ext::number<double>> timeline_time;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS_ANIMATION_PLAYBACK_EVENT_HPP

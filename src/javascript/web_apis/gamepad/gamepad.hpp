#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP

#include "dom_object.hpp"
namespace gamepad {class gamepad;}

#include USE_INNER_TYPES(gamepad)
#include USE_INNER_TYPES(hr_time)
namespace gamepad {class gamepad_button;}


class gamepad::gamepad
        : public virtual dom_object
{
public constructors:
    gamepad();

public js_properties:
    ext::property<ext::string> id;
    ext::property<ext::number<long>> index;
    ext::property<ext::boolean> connected;

    ext::property<hr_time::dom_high_res_time_stamp> timestamp;
    ext::property<detail::gamepad_mapping_type_t> mapping;
    ext::property<ext::vector<ext::number<double>>*> axes;
    ext::property<ext::vector<gamepad_button*>*> buttons;

private js_slots:
    ext::slot<ext::boolean> s_connected;
    ext::slot<hr_time::dom_high_res_time_stamp> s_timestamp;
    ext::slot<ext::vector<ext::number<double>>*> s_axes;
    ext::slot<ext::vector<gamepad_button*>*> s_buttons;
    ext::slot<ext::boolean> s_exposed;

    ext::slot<ext::map<ext::number<int>, ext::number<int>>*> s_axis_mapping;
    ext::slot<ext::vector<ext::number<int>>*> s_axis_minimums;
    ext::slot<ext::vector<ext::number<int>>*> s_axis_maximums;

    ext::slot<ext::map<ext::number<int>, gamepad_button*>*> s_button_mapping;
    ext::slot<ext::vector<ext::number<int>>*> s_button_minimums;
    ext::slot<ext::vector<ext::number<int>>*> s_button_maximums;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(connected) {return s_connected();}
    DEFINE_CUSTOM_GETTER(timestamp) {return ext::round(s_timestamp(), 5);}
    DEFINE_CUSTOM_GETTER(axes) {return s_axes();}
    DEFINE_CUSTOM_GETTER(buttons) {return s_buttons();};
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP

#include "dom_object.hpp"
namespace gamepad {class gamepad;}

#include USE_INNER_TYPES(gamepad)
#include USE_INNER_TYPES(high_resolution_time)
namespace gamepad {class gamepad_button;}


class gamepad::gamepad
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(gamepad);
    gamepad();

public js_properties:
    ext::property<ext::string> id;
    ext::property<ext::number<long>> index;
    ext::property<ext::boolean> connected;

    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> timestamp;
    ext::property<detail::gamepad_mapping_type_t> mapping;
    ext::property<std::unique_ptr<ext::vector<ext::number<double>>>> axes;
    ext::property<std::unique_ptr<ext::vector<gamepad_button*>>> buttons;

private js_slots:
    ext::slot<ext::boolean> s_connected;
    ext::slot<high_resolution_time::detail::dom_high_res_time_stamp_t> s_timestamp;
    ext::slot<ext::vector<ext::number<double>>> s_axes;
    ext::slot<ext::vector<gamepad_button*>> s_buttons;
    ext::slot<ext::boolean> s_exposed;

    ext::slot<ext::map<ext::number<int>, ext::number<int>>> s_axis_mapping;
    ext::slot<ext::vector<ext::number<int>>> s_axis_minimums;
    ext::slot<ext::vector<ext::number<int>>> s_axis_maximums;

    ext::slot<ext::map<ext::number<int>, gamepad_button*>> s_button_mapping;
    ext::slot<ext::vector<ext::number<int>>> s_button_minimums;
    ext::slot<ext::vector<ext::number<int>>> s_button_maximums;

private cpp_accessors:
    DEFINE_GETTER(timestamp);
    DEFINE_GETTER(buttons);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_HPP
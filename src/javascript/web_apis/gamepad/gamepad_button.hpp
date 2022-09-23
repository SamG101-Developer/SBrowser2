#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_HPP

#include "dom_object.hpp"
namespace gamepad {class gamepad_button;}


class gamepad::gamepad_button
        : public dom_object
{
public constructors:
    gamepad_button() = default;

private js_properties:
    ext::property<ext::boolean> pressed;
    ext::property<ext::boolean> touched;
    ext::property<ext::number<double>> value;

private js_slots:
    ext::slot<ext::boolean> s_pressed;
    ext::slot<ext::boolean> s_touched;
    ext::slot<ext::number<double>> s_value;

public cpp_properties:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private js_properties:
    DEFINE_CUSTOM_GETTER(pressed) {return s_pressed();}
    DEFINE_CUSTOM_GETTER(touched) {return s_touched();}
    DEFINE_CUSTOM_GETTER(value) {return s_value();}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_GAMEPAD_GAMEPAD_BUTTON_HPP

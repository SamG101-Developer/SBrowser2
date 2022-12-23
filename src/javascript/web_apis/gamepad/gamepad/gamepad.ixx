module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.gamepad.gamepad;
import apis.dom_object;

import apis.hr_time.types;
import apis.gamepad.types;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(gamepad, gamepad) final
        : public virtual dom_object
{
public constructors:
    gamepad();
    MAKE_PIMPL(gamepad);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

private js_properties:
    DEFINE_GETTER(id, ext::string_view);
    DEFINE_GETTER(index, ext::number<long>);
    DEFINE_GETTER(connected, ext::boolean);

    DEFINE_GETTER(timestamp, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(mapping, detail::gamepad_mapping_type_t);
    DEFINE_GETTER(axes, ext::span<ext::number<double>>);
    DEFINE_GETTER(buttons, ext::span<gamepad_button*>);
};

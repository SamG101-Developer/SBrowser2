module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.web_bluetooth.bluetooth;
import apis.dom.event_target;

import ext.boolean;
import ext.promise;
import ext.enums;
import ext.tuple;
import ext.vector;

import js.env.module_type;

namespace web_bluetooth {class bluetooth_device;}


DEFINE_PUBLIC_CLASS(web_bluetooth, bluetooth)
        : public dom::event_target
{
public typedefs:
    using request_device_options_t = ext::map<ext::any, ext::string>;

public constructors:
    bluetooth();
    MAKE_PIMPL(bluetooth);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

public js_methods:
    auto get_availablility() -> ext::promise<ext::boolean>;
    auto get_devices() -> ext::promise<ext::vector<bluetooth_device*>>
    auto request_device(request_device_options_t&& options = {}) -> ext::promise<bluetooth_device*>;

public js_properties:
    DEFINE_GETTER(referring_device, bluetooth_device*);
};

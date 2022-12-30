module;
#include "ext/macros.hpp"


export module apis.web_bluetooth.bluetooth:p;
import apis.dom.event_target;
import apis.web_bluetooth.types;

import ext.any;
import ext.map;
import ext.memory;
import ext.promise;

namespace web_bluetooth {class bluetooth_device;}


DEFINE_PRIVATE_CLASS(web_bluetooth, bluetooth)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(bluetooth);

public:
    ext::map<detail::bluetooth_device_t*, bluetooth_device*> device_instance_map;
    ext::map<detail::bluetooth_cache_t*, ext::promise<ext::any>> attribute_instance_map;
    std::observer_ptr<bluetooth_device> referring_device;
};

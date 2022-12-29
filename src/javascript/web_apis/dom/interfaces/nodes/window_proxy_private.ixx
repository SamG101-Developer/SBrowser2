module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.window_proxy_private;
import apis.dom_object_private;

import apis.dom.types;
import ext.core;


DEFINE_PRIVATE_CLASS(dom, window_proxy) final
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(window_proxy);

public:
    std::observer_ptr<window> window;
};

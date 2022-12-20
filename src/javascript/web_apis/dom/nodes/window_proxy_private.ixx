module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.window_proxy_private;
import apis.dom_object_private;

import ext.memory;

namespace dom {class window;}


DEFINE_PRIVATE_CLASS(dom, window_proxy) final
        : virtual dom_object_private
{
    MAKE_QIMPL(window_proxy);

    std::observer_ptr<window> window;
};

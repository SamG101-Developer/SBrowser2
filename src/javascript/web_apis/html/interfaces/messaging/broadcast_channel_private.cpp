module;
#include "ext/macros.hpp"


module apis.html.broadcast_channel:p;

import apis.dom.window;
import apis.dom.document;
import apis.html.worker_global_scope;


import ext.boolean;
import js.env.realms;


auto html::broadcast_channel_private::is_eligible_for_messaging() const -> ext::boolean
{
    ACCESS_QIMPL;
    auto e = js::env::env::relevant(q);

    if (decltype(auto) window = e.cpp.global<dom::window*>())
        return window->d_func()->document->d_func()->fully_active();

    if (decltype(auto) worker = e.cpp.global<worker_global_scope*>())
        return !worker->d_func()->closing_flag && !worker->d_func()->worker->suspendable_worker();

    return false;
}

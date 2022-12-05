#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/memory.ixx"
namespace dom::nodes {class window;}


DEFINE_PRIVATE_CLASS(dom::nodes, window_proxy)
        : virtual dom_object_private
{
    MAKE_QIMPL(window_proxy);

    std::observer_ptr<window> window;
    auto Window() const -> v8::Local<v8::Object>; // TODO : ?
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_PRIVATE_HPP

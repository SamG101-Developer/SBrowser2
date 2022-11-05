#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/memory.hpp"
namespace dom::nodes {class window;}


DEFINE_PRIVATE_CLASS(dom::nodes, window_proxy) : dom_object_private
{
    std::observer_ptr<window> window;
    auto Window() const -> v8::Local<v8::Object>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_WINDOW_PROXY_PRIVATE_HPP

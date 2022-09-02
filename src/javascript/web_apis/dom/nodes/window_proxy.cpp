#include "window_proxy.hpp"


auto dom::nodes::window_proxy::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::convert<window_proxy*>::to_v8(isolate, this);
}

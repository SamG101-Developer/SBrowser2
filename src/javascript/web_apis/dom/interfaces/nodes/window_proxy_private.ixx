module;
#include "ext/macros.hpp"


export module apis.dom.window_proxy:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, window_proxy) final
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(window_proxy);

public:
    std::observer_ptr<window> window;
};

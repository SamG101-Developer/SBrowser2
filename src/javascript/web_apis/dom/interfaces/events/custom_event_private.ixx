module;
#include "ext/macros.hpp"

export module apis.dom.custom_event:p;
import apis.dom.event;


DEFINE_PRIVATE_CLASS(dom, custom_event)
        : event_private
{
public:
    MAKE_QIMPL(custom_event);

public:
    ext::any detail;
};

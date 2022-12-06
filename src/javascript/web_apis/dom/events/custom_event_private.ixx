module;
#include "ext/macros/pimpl.hpp"

export module apis.dom.custom_event_private;
import apis.dom.event_private;
import ext.any;


DEFINE_PRIVATE_CLASS(dom, custom_event)
        : event_private
{
    MAKE_QIMPL(custom_event);

    ext::any detail;
};

module;
#include "ext/macros.hpp"


export module apis.clipboard.clipboard_event;
import apis.dom.event;

import ext.any;
import ext.map;
import ext.string;
import ext.tuple;

import js.env.module_type;

namespace html {class data_transfer;}


DEFINE_PUBLIC_CLASS(clipboard, clipboard_event)
        : public dom::event
{
public typedefs:
    using clipboard_event_init_t = ext::map<ext::string, ext::any>;

public constructors:
    clipboard_event(ext::string&& event_type, clipboard_event_init_t&& event_init = {});
    MAKE_PIMPL(clipboard_event);
    MAKE_V8_AVAILABLE(WINDOW);
};

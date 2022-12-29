module;
#include <function2/function2.hpp>
#include "ext/macros/macros.hpp"


export module apis.dom.event_target:t;
import apis.dom.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(dom)
{
    using event_listener_callback_t = ext::function<void(ext::string, event*), void()>;
    using event_listener_options_t = ext::map<ext::string, ext::any>;
    using add_event_listener_options_t = ext::map<ext::string, ext::any>;
};

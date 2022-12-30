module;
#include "ext/macros.hpp"


export module apis.dom.event_target:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, event_target)
        : virtual dom_object_private
{
public:
    using event_listener_callback_t = ext::function<void(ext::string, event*), void()>;
    using event_listener_options_t = ext::map<ext::string, ext::any>;
    using add_event_listener_options_t = ext::map<ext::string, ext::any>;
    MAKE_QIMPL(event_target);

public:
    auto get_the_parent(event* event) -> event_target*;
    auto remove_all_event_listeners() -> void;

public:
    ext::vector<ext::map<ext::string, ext::any>> event_listeners;
};

module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.event_target_private;
import apis._.dom_object_private;
import ext.any;
import ext.boolean;
import ext.concepts;
import ext.map;
import ext.string;
import ext.vector;

namespace dom {class event_target;}
namespace dom {class event;}


DEFINE_PRIVATE_CLASS(dom, event_target)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(event_target);

public:
    ext::vector<ext::map<ext::string, ext::any>> event_listeners;

public:
    auto get_the_parent(event* event) -> event_target*;

    template <ext::inherit<event> T=event>
    auto fire_event(ext::string&& e, ext::map<ext::string, ext::any>&& init = {}) -> ext::boolean;

    auto remove_all_event_listeners() -> void;
    auto retarget(const event_target* other) const -> event_target*;
};

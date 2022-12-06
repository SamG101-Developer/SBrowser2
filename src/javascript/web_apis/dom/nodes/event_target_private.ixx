module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.event_target_private;
import apis._.dom_object_private;
import ext.vector;
import ext.map;
import ext.string;
import ext.any;

namespace dom {class event_target;}
namespace dom {class event;}


DEFINE_PRIVATE_CLASS(dom, event_target)
        : virtual dom_object_private
{
    MAKE_QIMPL(event_target);

    auto get_the_parent(event* event) -> event_target*;
    ext::vector<ext::map<ext::string, ext::any>> event_listeners;
};

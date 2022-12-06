module;
#include "ext/macros/pimpl.hpp"
#include <memory>


export module apis.dom.abort_controller_private;
import apis._.dom_object_private;

namespace dom {class abort_signal;}


DEFINE_PRIVATE_CLASS(dom, abort_controller)
        : virtual dom_object_private
{
    std::unique_ptr<abort_signal> signal;
};

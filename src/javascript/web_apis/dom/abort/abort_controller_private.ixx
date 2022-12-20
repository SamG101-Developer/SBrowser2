module;
#include "ext/macros/pimpl.hpp"
#include <memory>


export module apis.dom.abort_controller_private;
import apis.dom_object_private;
import apis.dom.types;


DEFINE_PRIVATE_CLASS(dom, abort_controller)
        : virtual dom_object_private
{
    std::unique_ptr<abort_signal> signal;
};

module;
#include "ext/macros.hpp"
#include <memory>


export module apis.dom.abort_controller:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, abort_controller)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(abort_controller);

public:
    std::unique_ptr<abort_signal> signal;
};

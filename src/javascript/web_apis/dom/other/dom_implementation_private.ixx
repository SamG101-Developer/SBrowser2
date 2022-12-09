module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.dom_implementation;
import apis._.dom_object_private;

import ext.memory;


DEFINE_PRIVATE_CLASS(dom, dom_implementation) final
        : virtual dom_object_private
{
    MAKE_QIMPL(dom_implementation);

    std::observer_ptr<nodes::document> document;
};

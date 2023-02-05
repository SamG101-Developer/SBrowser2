module;
#include "ext/macros.hpp"


export module apis.dom.dom_implementation:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, dom_implementation) final
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(dom_implementation);

public:
    std::observer_ptr<document> document;
};

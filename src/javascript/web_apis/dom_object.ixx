module;
#include "ext/macros.hpp"


export module apis.dom_object;
import ext.core;
import js.env.module_type;

export import :p;


export class dom_object
{
public constructors:
    dom_object();
    dom_object(dom_object&&) noexcept = default;
    virtual ~dom_object() = default;
    MAKE_PIMPL(dom_object);
    MAKE_V8_AVAILABLE(_);
    MAKE_STRINGIFIER;

protected:
    std::unique_ptr<dom_object_private> d_ptr;
};

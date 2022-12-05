module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/other.hpp"
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <memory>


export module apis.dom_object;
import ext.string;
import ext.tuple;
import ext.type_traits;

class dom_object_private;

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

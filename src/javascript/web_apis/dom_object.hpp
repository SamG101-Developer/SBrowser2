#ifndef SBROWSER2_DOM_OBJECT_HPP
#define SBROWSER2_DOM_OBJECT_HPP

class dom_object_private;

#include "ext/any.hpp"
#include "ext/custom_operator.hpp"
#include "ext/functional.hpp"
#include "ext/keywords.hpp"
#include "ext/pimpl.hpp"
#include "ext/property.hpp"
#include "ext/string.hpp"
#include "ext/type_traits.hpp"
#include <memory>

#include "javascript/interop/expose_macros.hpp"


#define DOM_CTORS(type)  \
    type();              \
    DISALLOW_COPY(type); \
    ALLOW_MOVE(type)


#define MAKE_STRINGIFIER \
private:                 \
    operator ext::string() const


class dom_object
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


#endif //SBROWSER2_DOM_OBJECT_HPP

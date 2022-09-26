#ifndef SBROWSER2_DOM_EXCEPTION_HPP
#define SBROWSER2_DOM_EXCEPTION_HPP

#include "dom_object.hpp"
namespace dom::other {class dom_exception;}

#include "ext/concepts.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(dom)

#include "dom/other/dom_exception_private.hpp"


class dom::other::dom_exception
        : public virtual dom_object
{
public constructors:
    dom_exception() = default;
    dom_exception(ext::string&& message, detail::dom_exception_error_t&& type);
    MAKE_PIMPL(dom_exception);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_DOM_EXCEPTION_HPP

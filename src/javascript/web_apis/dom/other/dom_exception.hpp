#ifndef SBROWSER2_DOM_EXCEPTION_HPP
#define SBROWSER2_DOM_EXCEPTION_HPP

#include "dom_object.hpp"
namespace dom::other {class dom_exception;}

#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(dom)

#include "dom/other/dom_exception_private.hpp"


class dom::other::dom_exception
        : public virtual dom_object
{
public constructors:
    dom_exception() = default;
    dom_exception(ext::string&& message, v8_custom_error_t type);

public js_properties:
    ext::property<ext::string> message;
    ext::property<v8_custom_error_t> type;

private cpp_members:
    operator std::exception_ptr() const;
    MAKE_PIMPL(dom_exception);
    MAKE_V8_AVAILABLE;

private cpp_accessors:
    DEFINE_CUSTOM_GETTER(message) {return d_ptr->message;}
    DEFINE_CUSTOM_GETTER(type) {return d_ptr->type;};
};


#endif //SBROWSER2_DOM_EXCEPTION_HPP

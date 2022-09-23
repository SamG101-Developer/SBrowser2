#ifndef SBROWSER2_DOM_EXCEPTION_HPP
#define SBROWSER2_DOM_EXCEPTION_HPP

#include "dom_object.hpp"
namespace dom::other {class dom_exception;}

#include "ext/string.hpp"
#include <magic_enum.hpp>
#include INCLUDE_INNER_TYPES(dom)

#include "dom/other/dom_exception_private.hpp"


class dom::other::dom_exception
        : public virtual dom_object
{
public constructors:
    dom_exception() = default;
    dom_exception(ext::string&& message, v8_custom_error_t type);
    MAKE_PIMPL(dom_exception);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(message, ext::string) {return d_ptr->message;}
    DEFINE_GETTER(code, v8_custom_error_t) {return d_ptr->code;};
    DEFINE_GETTER(name, ext::string_view) {return magic_enum::enum_name(d_ptr->code);}
};


#endif //SBROWSER2_DOM_EXCEPTION_HPP

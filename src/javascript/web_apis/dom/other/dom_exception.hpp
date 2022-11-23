#ifndef SBROWSER2_DOM_EXCEPTION_HPP
#define SBROWSER2_DOM_EXCEPTION_HPP

#include "base_exception.hpp"
namespace dom::other {class dom_exception;}
namespace dom::other {class dom_exception_private;}

#include INCLUDE_INNER_TYPES(dom)
#include "ext/concepts.hpp"
#include "ext/string.hpp"
namespace dom::abort {class abort_signal;}


class dom::other::dom_exception
        : public base_exception<detail::dom_exception_error_t>
{
public friends:
    friend class dom::abort::abort_signal;

public constructors:
    dom_exception(ext::u8string&& message, exception_t type);
    MAKE_PIMPL(dom_exception);
    MAKE_V8_AVAILABLE(ALL);
    MAKE_SERIALIZABLE;
};


#endif //SBROWSER2_DOM_EXCEPTION_HPP

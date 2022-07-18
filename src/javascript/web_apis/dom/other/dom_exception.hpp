#ifndef SBROWSER2_DOM_EXCEPTION_HPP
#define SBROWSER2_DOM_EXCEPTION_HPP

#include "dom_object.hpp"
namespace dom::other {class dom_exception;}

#include "ext/string.hpp"
enum v8_custom_error_t;


class dom::other::dom_exception
        : public virtual web_apis::dom_object
{
public constructors:
    dom_exception(ext::string&& message, v8_custom_error_t type);

public js_properties:
    ext::property<ext::string> message;
    ext::property<int> type;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_DOM_EXCEPTION_HPP

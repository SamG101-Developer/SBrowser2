#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_HPP

#include "dom_object.hpp"
namespace html::mixins {class validatable;}

namespace html::other {class validity_state;}


class html::mixins::validatable
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(validatable);
    validatable() = default;

public js_methods:
    auto check_validity() -> ext::boolean;
    auto report_validity() -> ext::boolean;
    auto set_custom_validity(ext::string&& error) -> void;

public js_properties:
    ext::property<ext::boolean> will_validate;
    ext::property<other::validity_state*> validity;
    ext::property<ext::string> validation_message;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_HPP

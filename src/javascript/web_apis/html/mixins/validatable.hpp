#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_HPP

#include "dom_object.hpp"
namespace html::mixins {class validatable;}
namespace html::mixins {class validatable_private;}

namespace html::other {class validity_state;}


class html::mixins::validatable
        : public virtual dom_object
{
public constructors:
    validatable();
    MAKE_PIMPL(validatable);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto check_validity() -> ext::boolean;
    auto report_validity() -> ext::boolean;
    auto set_custom_validity(ext::string&& error) -> void;

private js_properties:
    DEFINE_GETTER(will_validate, ext::boolean);
    DEFINE_GETTER(validity, other::validity_state*);
    DEFINE_GETTER(validation_message, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_VALIDATABLE_HPP

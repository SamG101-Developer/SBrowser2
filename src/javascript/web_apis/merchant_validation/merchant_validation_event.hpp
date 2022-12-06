#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_MERCHANT_VALIDATION_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_MERCHANT_VALIDATION_EVENT_HPP

// Inheritance Includes & This Class

namespace merchant_validation {class merchant_validation_event;}
namespace merchant_validation {class merchant_validation_event_private;}

// Other Includes & Forward Declarations



class merchant_validation::merchant_validation_event
        : public dom::events::event
{
public constructors:
    merchant_validation_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init);
    MAKE_PIMPL(merchant_validation_event);
    MAKE_V8_AVAILABLE(WINDOW | SECURE);

public js_methods:
    auto complete(ext::promise<ext::any>&& merchant_session_promise) -> void;

public js_properties:
    DEFINE_GETTER(method_name, ext::string_view);
    DEFINE_GETTER(validation_url, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_MERCHANT_VALIDATION_EVENT_HPP

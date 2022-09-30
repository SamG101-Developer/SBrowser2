#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_HPP

#include "dom_object.hpp"
namespace payment::handler {class payment_manager;}

namespace payment::handler {class payment_instruments;}

#include "payment_manager_private.hpp"


class payment::handler::payment_manager
        : public virtual dom_object
{
public constructors:
    payment_manager();
    MAKE_PIMPL(payment_manager);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(instruments, payment_instruments*);
    DEFINE_GETTER(user_hint, ext::string);

    DEFINE_SETTER(user_hint, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_HPP

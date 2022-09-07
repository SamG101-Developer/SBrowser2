#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_HPP

#include "dom_object.hpp"
namespace payment::handler {class payment_manager;}

namespace payment::handler {class payment_instruments;}


class payment::handler::payment_manager
        : public virtual dom_object
{
public js_properties:
    ext::property<std::unique_ptr<payment_instruments>> instruments;
    ext::property<ext::string> user_hint;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_HPP

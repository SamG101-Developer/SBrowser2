#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include "ext/string.hpp"
namespace payment::handler {class payment_instruments;}


DEFINE_PRIVATE_CLASS(payment::handler, payment_manager) : virtual dom_object_private
{
    std::unique_ptr<payment_instruments> instruments;
    ext::string user_hint;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PAYMENT_HANDLER_PAYMENT_MANAGER_PRIVATE_HPP

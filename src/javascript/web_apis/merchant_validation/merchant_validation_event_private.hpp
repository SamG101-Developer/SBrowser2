#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_MERCHANT_VALIDATION_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_MERCHANT_VALIDATION_EVENT_PRIVATE_HPP

#include "ext/pimpl.ixx"



DEFINE_PRIVATE_CLASS(merchant_validation, merchant_validation_event)
        : dom::events::event_private
{
    MAKE_QIMPL(merchant_validation_event);

    ext::string method_name;
    std::unique_ptr<url::detail::url_t> validation_url;
    ext::boolean wait_for_update;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MERCHANT_VALIDATION_MERCHANT_VALIDATION_EVENT_PRIVATE_HPP

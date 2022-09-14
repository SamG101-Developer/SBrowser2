#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIALS_CONTAINER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIALS_CONTAINER_HPP

#include "dom_object.hpp"
namespace webappsec::credential_management {class credentials_container;}

#include USE_INNER_TYPES(webappsec_credential_management)
#include "ext/promise.hpp"
namespace webappsec::credential_management {class credential;}


class webappsec::credential_management::credentials_container
        : public virtual dom_object
{
public js_methods:
    auto get(detail::credential_request_options_t&& options = {}) -> ext::promise<credential*>;
    auto store(credential* credential_object) -> ext::promise<credential*>;
    auto create(detail::credential_request_options_t&& options = {}) -> ext::promise<credential*>;

    auto prevent_select_access() -> ext::promise<void>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIALS_CONTAINER_HPP
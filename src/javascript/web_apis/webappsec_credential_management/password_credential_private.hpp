#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_PASSWORD_CREDENTIAL_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_PASSWORD_CREDENTIAL_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "webappsec_credential_management/credential_private.hpp"
#include "webappsec_credential_management/mixins/credential_user_data_private.hpp"
namespace webappsec::credential_management {class password_credential;}

#include INCLUDE_INNER_TYPES(webappsec_credential_management)


DEFINE_PRIVATE_CLASS(webappsec::credential_management, password_credential)
        : webappsec::credential_management::credential_private
        , webappsec::credential_management::mixins::credential_user_data_private
{
    MAKE_QIMPL(password_credential);

    const ext::string type = u"password";
    const detail::discovery_t discovery = detail::discovery_t::CREDENTIAL_STORE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_PASSWORD_CREDENTIAL_PRIVATE_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_PASSWORD_CREDENTIAL_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_PASSWORD_CREDENTIAL_HPP

// Inheritance Includes & This Class
#include "webappsec_credential_management/credential.hpp"
#include "webappsec_credential_management/mixins/credential_user_data.hpp"
namespace webappsec::credential_management {class password_credential;}
namespace webappsec::credential_management {class password_credential_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(webappsec_credential_management)
namespace html::elements {class html_form_element;}


class webappsec::credential_management::password_credential
        : public webappsec::credential_management::credential
        , public webappsec::credential_management::mixins::credential_user_data
{
public constructors:
    password_credential(const html::elements::html_form_element* form);
    password_credential(detail::password_credential_data_t&& data);
    MAKE_PIMPL(password_credential);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(password, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_PASSWORD_CREDENTIAL_HPP

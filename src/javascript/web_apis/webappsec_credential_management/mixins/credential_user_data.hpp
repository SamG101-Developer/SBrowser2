#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_HPP

#include "dom_object.hpp"
namespace webappsec::credential_management::mixins {class credential_user_data;}
namespace webappsec::credential_management::mixins {class credential_user_data_private;}


class webappsec::credential_management::mixins::credential_user_data
        : public virtual dom_object
{
public constructors:
    credential_user_data();
    MAKE_PIMPL(credential_user_data);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(name, ext::string_view);
    DEFINE_GETTER(icon_url, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_HPP

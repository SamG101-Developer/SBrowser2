#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_HPP

#include "dom_object.hpp"
namespace webappsec::credential_management {class credential_user_data;}


class webappsec::credential_management::credential_user_data
        : public virtual dom_object
{
public js_properties:
    ext::property<ext::string> name;
    ext::property<ext::string> icon_url;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(url)
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(webappsec::credential_management::mixins, credential_user_data) : dom_object_private
{
    MAKE_QIMPL(credential_user_data);

    ext::string name;
    std::unique_ptr<url::detail::url_t> icon_url;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_MIXINS_CREDENTIAL_USER_DATA_PRIVATE_HPP
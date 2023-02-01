#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_HPP


namespace webappsec::credential_management {class credential;}
namespace webappsec::credential_management {class credential_private;}




class webappsec::credential_management::credential
        : public virtual dom_object
{
public constructors:
    credential();
    MAKE_PIMPL(credential);
    MAKE_V8_AVAILABLE;

private js_methods:
    static auto is_conditional_mediation_available() -> ext::promise<ext::boolean>;

private js_properties:
    DEFINE_GETTER(id, ext::string_view);
    DEFINE_GETTER(type, ext::string_view);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_HPP

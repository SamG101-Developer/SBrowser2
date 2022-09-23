#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_HPP

#include "dom_object.hpp"
namespace webappsec::credential_management {class credential;}

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(webappsec_credential_management)
#include "ext/promise.hpp"


class webappsec::credential_management::credential
        : public virtual dom_object
{
public constructors:
    credential() = default;

public js_methods:
    static auto is_conditional_mediation_available() -> ext::promise<ext::boolean>;

private js_properties:
    ext::property<ext::string> id;
    ext::property<ext::string> type;

private js_slot_methods:
    auto s_collect_from_credential_store(const html::detail::origin_t& origin, detail::credential_request_options_t&& options, ext::boolean same_origin_with_ancestors) -> ext::set<credential*>;
    auto s_discover_from_external_source(const html::detail::origin_t& origin, detail::credential_request_options_t&& options, ext::boolean same_origin_with_ancestors) -> credential*;
    auto s_store(credential* credential, ext::boolean same_origin_with_ancestors) -> credential*;
    auto s_create(const html::detail::origin_t& origin, detail::credential_request_options_t&& options, ext::boolean same_origin_with_ancestors) -> credential*;

private js_slots:
    ext::slot<ext::string> s_type;
    ext::slot<detail::discovery_t> s_discovery;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private js_properties:
    DEFINE_CUSTOM_GETTER(type) {return s_type();}
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_HPP

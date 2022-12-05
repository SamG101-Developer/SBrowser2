#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include INCLUDE_INNER_TYPES(webappsec_credential_management)
#include INCLUDE_INNER_TYPES(html)
namespace webappsec::credential_management {class credential;}


DEFINE_PRIVATE_CLASS(webappsec::credential_management, credential) : virtual dom_object_private
{
    MAKE_QIMPL(credential);

    virtual auto collect_from_credential_store(
            const html::detail::origin_t& origin,
            detail::credential_request_options_t&& options,
            ext::boolean same_origin_with_ancestors)
            -> ext::set<credential*>;

    virtual auto discover_from_external_source(
            const html::detail::origin_t& origin,
            detail::credential_request_options_t&& options,
            ext::boolean same_origin_with_ancestors)
            -> credential*;

    virtual auto store(
            credential* c,
            ext::boolean same_origin_with_ancestors)
            -> credential*;

    virtual auto create(
            const html::detail::origin_t& origin,
            detail::credential_request_options_t&& options,
            ext::boolean same_origin_with_ancestors)
            -> credential*;

    ext::string id;
    ext::string type;
    detail::discovery_t discovery;
    std::shared_ptr<html::detail::origin_t> bound_origin;
};


auto webappsec::credential_management::credential_private::collect_from_credential_store(
        const html::detail::origin_t& origin,
        detail::credential_request_options_t&& options,
        ext::boolean same_origin_with_ancestors)
        -> ext::set<credential*>
{
    return {};
}


auto webappsec::credential_management::credential_private::discover_from_external_source(
        const html::detail::origin_t& origin,
        detail::credential_request_options_t&& options,
        ext::boolean same_origin_with_ancestors)
        -> credential*
{
    return nullptr;
}


auto webappsec::credential_management::credential_private::store(
        webappsec::credential_management::credential* c,
        ext::boolean same_origin_with_ancestors)
        -> credential*
{
    return nullptr;
}


auto webappsec::credential_management::credential_private::create(
        const html::detail::origin_t& origin,
        detail::credential_request_options_t&& options,
        ext::boolean same_origin_with_ancestors)
        -> credential*
{
    return nullptr;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_CREDENTIAL_PRIVATE_HPP

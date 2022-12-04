#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_DETAIL_ALGORITHM_INTERNALS_HPP


#include "ext/promise.ixx"
#include "ext/set.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(webappsec_credential_management)

namespace js::env {class env;}
namespace webappsec::credential_management {class credential;}


namespace webappsec::detail
{
    auto same_origin_with_ancestors(
            js::env::env& e)
            -> ext::boolean;

    auto requires_use_mediation(
            const html::detail::origin_t& origin)
            -> ext::boolean;

    auto relevant_credential_interface_objects(
            ext::map<ext::string, ext::any>&& options)
            -> ext::set<credential_management::credential*>;

    auto matchable_priori(
            detail::credential_request_options_t&& options)
            -> ext::boolean;

    auto request_credential(
            detail::credential_request_options_t&& options)
            -> ext::promise<credential_management::credential*>;

    auto collect_credentials(
            const html::detail::origin_t& origin,
            detail::credential_request_options_t&& options,
            ext::boolean same_origin_with_ancestors)
            -> ext::set<credential_management::credential*>;

    auto store_credential(
            credential_management::credential* credential)
            -> ext::promise<credential_management::credential*>;

    auto prevent_silent_access(
            js::env::env& e)
            -> ext::promise<void>;

    auto create_credential(
            detail::credential_request_options_t&& options)
            -> ext::promise<credential_management::credential*>;

    auto ask_user_to_choose_credentials(
            detail::credential_request_options_t&& options,
            const ext::set<credential_management::credential*>& credentials)
            -> credential_management::credential*;
}


struct webappsec::detail::credential_store_t
{
    ext::boolean prevent_silent_access_flag;
    ext::set<webappsec::credential_management::credential*> credentials;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_DETAIL_ALGORITHM_INTERNALS_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/promise.hpp"
#include "ext/set.hpp"
#include <v8-forward.h>
#include USE_INNER_TYPES(html)
#include USE_INNER_TYPES(webappsec_credential_management)

namespace webappsec::credential_management {class credential;}


namespace webappsec::detail
{
    auto same_origin_with_ancestors(
            v8::Local<v8::Object> settings)
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
            credential_management::credential* credential,
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

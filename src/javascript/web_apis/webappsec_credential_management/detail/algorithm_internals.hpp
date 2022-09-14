#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/set.hpp"
#include <v8-forward.h>
#include USE_INNER_TYPES(webappsec_credential_management)


namespace webappsec::detail
{
    auto same_origin_with_ancestors(
            v8::Local<v8::Object> settings)
            -> ext::boolean;

    auto relevant_credential_interface_objects(
            ext::map<ext::string, ext::any>&& options)
            -> ext::set<void*>;

    auto matchable_priori(
            detail::credential_request_options_t&& options)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_CREDENTIAL_MANAGEMENT_DETAIL_ALGORITHM_INTERNALS_HPP

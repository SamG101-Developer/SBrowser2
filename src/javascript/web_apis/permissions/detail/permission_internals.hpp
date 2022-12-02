#pragma once
#ifndef SBROWSER2_PERMISSION_INTERNALS_HPP
#define SBROWSER2_PERMISSION_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/functional.ixx"
#include "ext/optional.hpp"
#include "ext/map.ixx"
#include "ext/string.hpp"
#include "ext/variant.ixx"

#include INCLUDE_INNER_TYPES(permissions)
#include INCLUDE_INNER_TYPES(permissions_policy)

#include <v8-object.h>
namespace permissions {class permission_status;}

namespace permissions::detail
{
    auto get_current_permission_state(
            ext::string&& name,
            ext::optional<v8::Local<v8::Object>> environment_settings_object)
            -> permission_state_t;

    auto permission_state(
            permissions_descriptor_t&& permission_descriptor,
            ext::optional<v8::Local<v8::Object>> environment_settings_object)
            -> permission_state_t;

    auto request_permission_to_use(
            permissions_descriptor_t&& permission_descriptor)
            -> permission_state_t;

    auto prompt_user_to_choose(
            permissions_descriptor_t&& permission_descriptor,
            ext::boolean allow_multiple = false)
            -> ext::variant<ext::vector<permissions_policy::detail::feature_t>, permission_state_t>;

    auto extra_permissions_data()
            -> permissions_descriptor_t;

    auto default_permission_query_algorithm(
            permissions_descriptor_t&& permission_descriptor,
            permissions_result_t* status)
            -> void;

    auto react_to_user_revoking_permission()
            -> void;
};


struct permissions::detail::powerful_feature_t
{
    powerful_feature_t(ext::string&& powerful_feature_name);

    ext::string name;

    ext::number<long double> permission_life; // TODO : steps when it expires
    permission_state_t default_permission_state;

    auto permission_state_constraints() -> permissions_descriptor_t;
    auto extra_permissions_data_constraints() -> permissions_descriptor_t;
    auto permission_query_algorithm(permissions_descriptor_t&& permission_descriptor, permissions_result_t* status) -> void;

    ext::function<void()> permission_revocation_algorithm;
};


#endif //SBROWSER2_PERMISSION_INTERNALS_HPP

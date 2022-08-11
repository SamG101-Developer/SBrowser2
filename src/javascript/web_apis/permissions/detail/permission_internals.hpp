#pragma once
#include "permissions_policy/_typedefs.hpp"
#ifndef SBROWSER2_PERMISSION_INTERNALS_HPP
#define SBROWSER2_PERMISSION_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/optional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

#include "permissions/_typedefs.hpp"

#include <v8-object.h>
namespace permissions {class permission_status;}

namespace permissions::detail::permission_internals
{
    struct powerful_feature_t;

    auto get_current_permission_state(
            ext::string&& name,
            v8::Local<v8::Object> environment_settings_object)
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
            ext::boolean_view allow_multiple = ext::boolean::FALSE_())
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


struct permissions::detail::permission_internals::powerful_feature_t
{
    ext::string name;

    ext::number<long double> permission_life; // TODO : steps when it expires
    permission_state_t default_permission_state;

    auto permission_state_constraints() -> permissions_descriptor_t;
    auto extra_permissions_data_constraints() -> permissions_descriptor_t;
    auto permission_query_algorithm(permissions_descriptor_t&& permission_descriptor, permissions_result_t* status) -> void;
    auto permission_revocation_algorithm() -> void;
};


#endif //SBROWSER2_PERMISSION_INTERNALS_HPP

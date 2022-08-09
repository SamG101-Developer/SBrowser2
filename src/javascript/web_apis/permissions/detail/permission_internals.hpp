#pragma once
#include "permissions_policy/_typedefs.hpp"
#ifndef SBROWSER2_PERMISSION_INTERNALS_HPP
#define SBROWSER2_PERMISSION_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"
#include "ext/optional.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

#include <v8-object.h>
namespace permissions {class permission_status;}

namespace permissions::detail::permission_internals
{
    enum class permission_state_t {DENIED, GRANTED, PROMPT};

    struct powerful_feature_t;

    auto get_current_permission_state(
            ext::string&& name,
            v8::Local<v8::Object> environment_settings_object)
            -> permission_state_t;

    auto permission_state(
            ext::map<ext::string, ext::any>&& permission_descriptor,
            ext::optional<v8::Local<v8::Object>> environment_settings_object)
            -> permission_state_t;

    auto request_permission_to_use(
            ext::map<ext::string, ext::any>&& permission_descriptor)
            -> permission_state_t;

    auto prompt_user_to_choose(
            ext::map<ext::string, ext::any>&& permission_descriptor,
            ext::boolean_view allow_multiple = ext::boolean::FALSE_())
            -> ext::variant<ext::vector<permissions_policy::detail::feature_t>, permission_state_t>;
};


struct permissions::detail::permission_internals::powerful_feature_t
{
    powerful_feature_t();

    using permissions_descriptor_type = ext::map<ext::string, ext::any>;
    using permissions_result_type = permission_status;
    using extra_permission_data_type = permission_state_t;

    ext::map<ext::string, ext::any> permission_state_constraints;
    ext::function<void(permissions_descriptor_type&& permission_descriptor, permissions_result_type* status)> permission_query_algorithm;
    ext::number<long double> permission_life; // TODO : steps when it expires
    permission_state_t default_permission_state;

    auto extra_permissions_data() -> ext::map<ext::string, ext::any>;
    auto extra_permissions_data_constraints() -> ext::map<ext::string, ext::any>;
};


#endif //SBROWSER2_PERMISSION_INTERNALS_HPP

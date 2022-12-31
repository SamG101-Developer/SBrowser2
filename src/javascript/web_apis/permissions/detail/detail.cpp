module;
#include "ext/macros.hpp"
#include <utility>


module apis.permissions.detail;
import apis.permissions.types;

import apis.dom.window;

import apis.webappsec_permissions_policy.detail;
import apis.webappsec_permissions_policy.types;

import ext.core;
import js.env.realms;
import js.env.settings;


auto permissions::detail::get_current_permission_state(
        ext::string&& name,
        const js::env::env& environment)
        -> permission_state_t
{
    // Create a mock 'permissions_descriptor' dictionary, with the "name" set the 'name' parameter. Return the
    // permission state for this 'permissions_descriptor', and the settings object.

    auto permissions_descriptor = permission_descriptor_t{{u"name", std::move(name)}};
    return permission_state(std::move(permissions_descriptor), environment);
}


auto permissions::detail::permission_state(
        permission_descriptor_t&& permission_descriptor,
        const js::env::env& environment)
        -> permission_state_t
{
    using namespace ext::literals;

    // Cannot determineb the state of a non-scure environment. Get the feature (permission whose state is to be
    // determined) from the 'permission_descriptor' map, and convert it to the enum value from the 'permissions_policy'
    // api.
    return_if (!environment.cpp.settings()->is_secure_context) permission_state_t::DENIED;
    auto feature_name = std::move(permission_descriptor[u"name"].to<webappsec::detail::feature_name_t>());
    auto feature = webappsec_permission_policy::detail::policy_controlled_feature_t::from_enum{feature_name};

    // If the feature exists, and the current global object has an associated document, then if the document isn't
    // allowed to use the certain feature, return the 'DENIED' state.
    if (document = environment.js.global<dom::window*>()->d_func()->document.get(); feature && document) // TODO : Worker
        return_if(!html::detail::allowed_to_use(document, std::move(feature_string))) permission_state_t::DENIED;

    // Generate the key and get the corresponding entry in the permission store -- this is a tuple of the permission,
    // key and state. If the permission exists for the key, then return the state in the tuple.
    auto key = generate_permission_key(descriptor, environment);
    auto entry = get_permission_store_entry(descriptor, std::move(key));
    return_if (entry[0_tag]) entry[2_tag];

    // TODO : final return value
}


auto permissions::detail::request_permission_to_use(
        permission_descriptor_t&& permission_descriptor)
        -> permission_state_t
{
    // Get the current permission state of the 'permission_descriptor'; if it isn't PROMPT, then the permission has
    // already been GRANTED / DENIED, so return, otherwise return the vlaue tat is returned from a user interaction with
    // the popup that is generated
    auto current_state = permission_state(std::move(permission_descriptor));
    return_if(current_state != permission_state_t::PROMPT) current_state;

    // TODO : ask the user for permission (GUI)
    auto express_permission = ext::boolean{};
    std::cin >> express_permission;

    current_state = express_permission ? permission_state_t::GRANTED : permission_state_t::DENIED;
    auto key = detail::generate_permission_key(descriptor, js::env::env::current());
    // TODO : Queue task

    return permission_state_t::DENIED;
}

#include "permission_internals.hpp"

#include "permissions/permission_status.hpp"
#include "html/detail/document_internals.hpp"
#include "storage/detail/storage_internals.hpp"

#include "gui/javascript_interop/registry.hpp"

#include <v8-local-handle.h>
#include <v8-object.h>
#include <magic_enum.hpp>


auto permissions::detail::get_current_permission_state(
        ext::string&& name,
        ext::optional<v8::Local<v8::Object>> environment_settings_object)
        -> permission_state_t
{
    auto e = js::env::env::current();

    // create a mock 'permissions_descriptor' dictionary, with the "name" set the 'name' parameter. return the
    // permission state for this 'permissions_descriptor', and the settings object
    permissions_descriptor_t permissions_descriptor {{u"name", std::move(name)}};
    return permission_state(std::move(permissions_descriptor), environment_settings_object.value_or(e.js.settings()));
}


auto permissions::detail::permission_state(
        permissions_descriptor_t&& permission_descriptor,
        ext::optional<v8::Local<v8::Object>> environment_settings_object)
        -> permission_state_t
{
    // the 'settings' is teh 'environment_settings_object' if provided, otherwise the current global object's settings
    // object. if the settings object isn't secure, then return from the method - permission states can only be read in
    // secure contexts
    auto e = js::env::env::current();
    auto settings = environment_settings_object.value_or(e.js.settings());
    // TODO : return if the settings object isn't secure

    // get the feature (permission whose state is to be determined) from the 'permission_descriptor' map, and convert
    // it to the enum value from the 'permissions_policy' api
    using permissions_policy::detail::feature_t;
    auto feature_string = permission_descriptor[u"name"].to<powerful_feature_t>().name;
    auto feature = magic_enum::enum_cast<feature_t>(std::move(feature_string));

    // if the feature exists, and the current global object has an associated document, then if teh document isn't
    // allowed to use the certain feature, return the 'DENIED' state TODO
    if (feature.has_value() && js::env::realms::has(current_global_object, "associated_document"))
    {
        auto* document = js::env::realms::get<dom::nodes::document*>(current_global_object, "associated_document");
        return_if(!html::detail::allowed_to_use(document, std::move(feature_string))) permission_state_t::DENIED;
    }

    // TODO : previous calls?
    // TODO : return correct permission
}


auto permissions::detail::request_permission_to_use(
        permissions_descriptor_t&& permission_descriptor)
        -> permission_state_t
{
    // get the current permission state of the 'permission_descriptor'; if it isn't PROMPT, then the permission has
    // already been GRANTED / DENIED, so return, otherwise return the vlaue tat is returned from a user interaction with
    // the popup that is generated
    auto current_state = permission_state(std::move(permission_descriptor), ext::nullopt);
    return_if(current_state != permission_state_t::PROMPT) current_state;
    return_if(gui::javascript_interop::permission_request_popup(permission_descriptor[u"name"].to<powerful_feature_t>().name)) permission_state_t::GRANTED;
    return permission_state_t::DENIED;
}


auto permissions::detail::default_permission_query_algorithm(
        permissions::detail::permissions_descriptor_t&& permission_descriptor,
        permissions::detail::permissions_result_t* status) -> void
{
    // get the permission state of the 'permission_descriptor', and set the state of the PermissionStatus object to the
    // permission state
    auto state = permission_state(std::move(permission_descriptor), ext::nullopt);
    auto state_string = magic_enum::enum_name(state);
    status->d_func()->state = state_string;
}


permissions::detail::powerful_feature_t::powerful_feature_t(
        ext::string&& powerful_feature_name)
        : name(powerful_feature_name)
{
    permission_query_algorithm = [](permissions_descriptor_t&& permission_descriptor, permissions_status* status) {status->d_func()->state = std::move(detail::permission_state(permission_descriptor));}
    permission_key_generation_algorithm = [](js::env::env& environment) {return environment.js.settings()->origin;};
    permission_key_comparison_algorithm = [](const permission_key_t& key_a, const permission_key_t& key_b) {return html::detail::same_origin(key_a, key_b);};
}

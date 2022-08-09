#include "permission_internals.hpp"

#include "permissions/permission_status.hpp"
#include "permissions_policy/_typedefs.hpp"
#include "html/detail/document_internals.hpp"

#include "gui/javascript_interop/registry.hpp"

#include <v8-local-handle.h>
#include <v8-object.h>
#include <magic_enum.hpp>


auto permissions::detail::permission_internals::get_current_permission_state(
        ext::string&& name,
        v8::Local<v8::Object> environment_settings_object)
        -> permission_state_t
{
    // create a mock 'permissions_descriptor' dictionary, with the "name" set the 'name' parameter. return the
    // permission state for this 'permissions_descriptor', and the settings object
    ext::map<ext::string, ext::any> permissions_descriptor {{"name", std::move(name)}};
    return permission_state(std::move(permissions_descriptor), environment_settings_object);
}


auto permissions::detail::permission_internals::permission_state(
        ext::map<ext::string, ext::any>&& permission_descriptor,
        ext::optional<v8::Local<v8::Object>> environment_settings_object)
        -> permission_state_t
{
    // the 'settings' is teh 'environment_settings_object' if provided, otherwise the current global object's settings
    // object. if the settings object isn't secure, then return from the method - permission states can only be read in
    // secure contexts
    JS_REALM_GET_CURRENT
    auto settings = environment_settings_object.value_or(current_global_object);
    // TODO : return if the settings object isn't secure

    // get the feature (permission whose state is to be determined) from the 'permission_descriptor' map, and convert
    // it to the enum value from the 'permissions_policy' api
    using permissions_policy::detail::feature_t;
    auto feature_string = permission_descriptor.at("name").to<ext::string>();
    auto feature = magic_enum::enum_cast<feature_t>(std::move(feature_string));

    // if the feature exists, and the current global object has an associated document, then if teh document isn't
    // allowed to use the certain feature, return the 'DENIED' state
    if (feature.has_value() && javascript::environment::realms_2::has(current_global_object, "associated_document"))
    {
        auto* document = javascript::environment::realms_2::get<dom::nodes::document*>(current_global_object, "associated_document");
        return_if(!html::detail::document_internals::allowed_to_use(document, std::move(feature_string))) permission_state_t::DENIED;
    }

    // TODO : previous calls?
    // TODO : return correct permission
}


auto permissions::detail::permission_internals::request_permission_to_use(
        ext::map<ext::string, ext::any>&& permission_descriptor)
        -> permission_state_t
{
    auto current_state = permission_state(std::move(permission_descriptor), ext::nullopt);
    return_if(current_state != permission_state_t::PROMPT) current_state;
    return_if(gui::javascript_interop::permission_request_popup(permission_descriptor.at("name").to<ext::string>())) permission_state_t::GRANTED;
    return permission_state_t::DENIED;
}


permissions::detail::permission_internals::powerful_feature_t::powerful_feature_t()
{
    permission_query_algorithm =
            [](permissions_descriptor_type&& permission_descriptor, permissions_result_type* status) mutable
            {status->state = (ext::string)magic_enum::enum_name(permission_state(std::move(permission_descriptor), ext::nullopt));};
}

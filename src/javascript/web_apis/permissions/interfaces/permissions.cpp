module apis.permissions.permissions;
import apis.permissions.types;

import apis.dom.window;

import apis.html.detail;
import apis.web_idl.detail;
import apis.webappsec_permissions_policy.types;

import ext.core;
import ext.js;

import js.env.realms;
import js.env.module_type;


auto permissions::permissions::query(
        detail::permission_descriptor_t&& permission_descriptor)
        -> ext::promise<std::unique_ptr<permission_status>>
{
    auto e = js::env::env::relevant(this);
    if (decltype(auto) window = e.cpp.global<dom::window*>(); !html::detail::is_fully_active(window->d_func()->document.get()))
        return web_idl::detail::create_rejected_promise<permission_status>(dom::other::dom_exception{u"Document must be active", INVALID_STATE_ERR}, e.js.realm());

    // Get the feature name and its corresponding policy controlled feature (using the permissions registry internally).
    // The 'feature' may be nullptr meaning that the feature doesn't exist.
    auto feature_name = std::move(permission_descriptor[u"name"].to<webappsec::detail::feature_name_t>());
    auto feature = webappsec_permission_policy::detail::policy_controlled_feature_t::from_enum{feature_name};

    // If the feature doesn't exist, then create a promise, reject it with a JavaScript TypeError, and return it -- this
    // means that querying the permission has failed, so no state is returned in the promise, and an error is created in
    // the promise rejection
    if (!feature)
        return web_idl::detail::create_rejected_promise<permission_status>(v8::Exception::TypeError(u"Feature doesn't exist"), e.js.realm());

    // Run the following steps in parallel as the permission querying would otherwise block the main thread (querying a
    // permission is a potentially blocking operation due to potentialy having to request explicit permission from the
    // user).
    _GO [&promise, permission_descriptor = std::move(permission_descriptor)] mutable
    {
        // Create a permission status and get the query from the PermissionStatus.[[Query]]. Get the powerful feature
        // for the query and run its query algorithm. Queue a task to resolve the promise.
        auto status = std::make_unique<permission_status>(std::move(permission_descriptor));
        decltype(auto) query = status->d_func()->query;
        decltype(auto) powerful_feature = detail::powerful_feature_t::from_enum(query[u"name"].to<webappsec::detail::feature_name_t>());
        powerful_feature->permission_query_algorithm(query, status);
        // TODO : Queue task
    });

    // Return the promise.
    return promise;
}

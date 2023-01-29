module;
#include "ext/macros.hpp"
#include "ext/macros/custom_operator.hpp"


module apis.storage.storage_manager;
import apis.storage.detail;
import apis.storage.types;

import apis.dom.detail;
import apis.dom.types;

import apis.permissions.detail;
import apis.web_idl.detail;

import js.env.realms;

import ext.core;
import ext.js;


auto storage::storage_manager::persisted() -> ext::promise<ext::boolean>
{
    // Get the relevant JavaScript realm for this StorageManager, and obtain its local storage shelf. create the promise
    // that will be returned.
    auto e = js::env::env::relevant(this);
    auto promise = ext::promise<ext::boolean>{};
    auto shelf = detail::obtain_local_storage_shelf(e);

    // If the shelf is a failure, reject the promise with a JavaScript TypeError, and effectively return (else-statement
    // is skipped obviously).
    if (!shelf.has_value())
        return web_idl::detail::reject_promise(promise, e.js.realm(), v8::Exception::TypeError());

    _GO [&promise, shelf = *shelf]
    {
        // Queue a microtask that will set the value of the promise to 'persisted', which is determined by
        // if the shelf's default storage bucket's mode is PERSISTENT.
        auto persisted = shelf->bucket_map[u"default"]->mode == detail::storage_bucket_mode_t::PERSISTENT;
        dom::detail::queue_task(
                html::detail::storage_task_source,
                ext::bind_front(web_idl::detail::resolve_promise, promise, persisted));
    };

    // Return the promise.
    return promise;
}


auto storage::storage_manager::persist() -> ext::promise<ext::boolean>
{
    // Get the relevant JavaScript realm for this StorageManager, and obtain its local storage shelf. create the promise
    // that will be returned.
    auto e = js::env::env::relevant(this);
    auto promise = ext::promise<ext::boolean>{};
    auto shelf = detail::obtain_local_storage_shelf(e);

    // If the shelf is a failure, reject the promise with a JavaScript TypeError, and effectively return (else-statement
    // is skipped obviously).
    if (!shelf.has_value())
        return web_idl::detail::reject_promise(promise, e.js.realm(), v8::Exception::TypeError());

    // Create a thread pool to execute the following lambda-steps in parallel (has to be in parallel because of the
    // task queuing.
    _GO [&promise, shelf = *shelf]
    {
        // Get the permission for the "persistent-storage" powerful feature, by constructing a dummy powerful feature
        // with the right name, and requesting permission to use it. TODO
        auto permission = permissions::detail::request_permission_to_use(permissions::detail::powerful_feature_t{.name="persistent-storage"});

        // Get the default bucket from the storage shelf.
        auto local_bucket = dom_cast<detail::local_storage_bucket_t*>(shelf->bucket_map[u"default"].get());
        auto persisted = local_bucket->mode == detail::storage_bucket_mode_t::PERSISTENT;

        // If the bucket's mode isn't PERSISTENT, and the permission has been granted, then continue with the steps.
        if (!persisted && permission == permissions::detail::permission_state_t::GRANTED)
        {
            // Set the buckets mode to PERSISTENT, catching any JavaScript errors in the process.
            JS_EXCEPTION_HANDLER;
            local_bucket->mode = detail::storage_bucket_mode_t::PERSISTENT;
            if (!JS_EXCEPTION_HAS_THROWN)
                persisted = true;

            // Queue a microtask that will set the value of the promise to 'persisted', which is determined by if the
            // shelf's default storage bucket's mode is PERSISTENT
            dom::detail::queue_task(
                    html::detail::storage_task_source,
                    BIND_FRONT(web_idl::detail::resolve_promise, promise, persisted));
        }
    };

    // Return the promise.
    return promise;
}


auto storage::storage_manager::estimate() -> ext::promise<detail::storage_estimate_t>
{
    // Get the relevant JavaScript realm for this StorageManager, and obtain its local storage shelf. create the promise
    // that will be returned.
    auto e = js::env::env::relevant(this);
    auto promise = ext::promise<detail::storage_estimate_t>{};
    auto shelf = detail::obtain_local_storage_shelf(e);

    // If the shelf is a failure, reject the promise with a JavaScript TypeError, and effectively return (else-statement
    // is skipped obviously).
    if (!shelf.has_value())
        return web_idl::detail::reject_promise(promise, e.js.realm(), v8::Exception::TypeError());

    // Create a thread pool to execute the following lambda-steps in parallel (has to be in parallel because of the task
    // queuing.
    _GO [&promise, shelf = *shelf]
    {
        // create an exception handler for JavaScript, get the 'usage' and 'quota' of the storage shelf, and
        // create a 'dictionary' containing these values
        JS_EXCEPTION_HANDLER;
        decltype(auto) usage = detail::storage_usage(*shelf);
        decltype(auto) quota = detail::storage_quota(*shelf);
        auto dictionary = detail::storage_estimate_t{{u"usage", usage}, {u"quota", quota}};

        // if an exception was thrown from JavaScript when trying to access these members, then queue a task
        // to reject the promise with a JavaScript TypeError
        if (JS_EXCEPTION_HAS_THROWN)
            dom::detail::queue_task(
                    html::detail::storage_task_source,
                    BIND_FRONT(web_idl::detail::reject_promise, promise, v8::Exception::TypeError()));

        // otherwise, queue a task to resolve the promise with the created 'dictionary'
        else
            dom::detail::queue_task(
                    html::detail::storage_task_source,
                    BIND_FRONT(web_idl::detail::resolve_promise, promise, dictionary));
    };

    // return the promise
    return promise;
}

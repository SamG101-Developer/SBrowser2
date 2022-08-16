#include "storage_manager.hpp"

#include "ext/threading.hpp"
#include "javascript/environment/realms_2.hpp"
#include "javascript/interop/annotations.hpp"

#include "dom/detail/observer_internals.hpp"
#include "permissions/detail/permission_internals.hpp"
#include "storage/detail/storage_internals.hpp"


auto storage::storage_manager::persisted()
        -> std::promise<ext::boolean>
{
    // get the relevant JavaScript realm for this StorageManager, and obtain its local storage shelf. create the promise
    // that will be returned
    JS_REALM_GET_RELEVANT(this);
    std::promise<ext::boolean> promise;
    auto shelf = detail::obtain_local_storage_shelf(this_relevant_global_object);

    // if the shelf is a failure, reject the promise with a JavaScript TypeError, and effectively return (else-statement
    // is skipped obviously)
    if (!shelf.has_value())
        promise.set_exception(); // TODO : JavaScript TypeError

    else
    {
        // create a thread pool to execute the following lambda-steps in parallel (has to be in parallel because of the
        // task queuing TODO : is this the case?)
        ext::thread_pool pool {1};
        pool.push_task(
                [&promise, shelf = std::move(*shelf)]
                {
                    // queue a microtask that will set the value of the promise to 'persisted', which is determined by
                    // if the shelf's default storage bucket's mode is PERSISTENT
                    using enum detail::storage_bucket_mode_t;
                    auto persisted = shelf.bucket_map.at("default").mode == PERSISTENT;
                    dom::detail::queue_microtask(
                            [&promise, persisted]
                            {promise.set_value(persisted);});
                });
    }

    // return the promise
    return promise;
}


auto storage::storage_manager::persist()
        -> std::promise<ext::boolean>
{
    // get the relevant JavaScript realm for this StorageManager, and obtain its local storage shelf. create the promise
    // that will be returned
    JS_REALM_GET_RELEVANT(this);
    std::promise<ext::boolean> promise;
    auto shelf = detail::obtain_local_storage_shelf(this_relevant_global_object);

    // if the shelf is a failure, reject the promise with a JavaScript TypeError, and effectively return (else-statement
    // is skipped obviously)
    if (!shelf.has_value())
        promise.set_exception(); // TODO : JavaScript TypeError

    else
    {
        // create a thread pool to execute the following lambda-steps in parallel (has to be in parallel because of the
        // task queuing TODO : is this the case?)
        ext::thread_pool pool{1};
        pool.push_task(
                [&promise, &shelf = *shelf]
                {
                    using permissions::detail::powerful_feature_t;
                    using enum storage::detail::storage_bucket_mode_t;
                    using enum permissions::detail::permission_state_t;

                    // get the permission for the "persistent-storage" powerful feature, by constructing a dummy
                    // powerful feature with the right name, and requesting permission to use it
                    auto permission = permissions::detail::request_permission_to_use(
                            {{"name", powerful_feature_t{.name="persistent-storage"}}});

                    // get the default bucket from the storage shelf
                    decltype(auto) bucket = shelf.bucket_map.at("default");
                    auto persisted = bucket.mode == PERSISTENT;

                    // if the bucket's mode isn't PERSISTENT, and the permission has been granted, then continue with
                    // the steps
                    if (!persisted && permission == GRANTED)
                    {
                        // set the buckets mode to PERSISTENT, catching any JavaScript errors in the process (TODO: why
                        //  would any be thrown?), and set 'persisted' to true if no errors are thrown
                        JS_EXCEPTION_HANDLER;
                        bucket.mode = PERSISTENT;
                        if (!JS_EXCEPTION_HAS_THROWN)
                            persisted = true;

                        // queue a microtask that will set the value of the promise to 'persisted', which is determined by
                        // if the shelf's default storage bucket's mode is PERSISTENT
                        dom::detail::queue_microtask(
                                [&promise, persisted]
                                {promise.set_value(persisted);});
                    }
                });
    }

    // return the promise
    return promise;
}


auto storage::storage_manager::estimate()
        -> std::promise<storage_estimate_t>
{
    // get the relevant JavaScript realm for this StorageManager, and obtain its local storage shelf. create the promise
    // that will be returned
    JS_REALM_GET_RELEVANT(this);
    std::promise<storage_estimate_t> promise;
    auto shelf = detail::obtain_local_storage_shelf(this_relevant_global_object);

    // if the shelf is a failure, reject the promise with a JavaScript TypeError, and effectively return (else-statement
    // is skipped obviously)
    if (!shelf.has_value())
        promise.set_exception(); // TODO : JavaScript TypeError

    else
    {
        // create a thread pool to execute the following lambda-steps in parallel (has to be in parallel because of the
        // task queuing TODO : is this the case?)
        ext::thread_pool pool{1};
        pool.push_task(
                [&promise, shelf = std::move(*shelf)]
                {
                    // create an exception handler for JavaScript, get the 'usage' and 'quota' of the storage shelf, and
                    // create a 'dictionary' containing these values
                    JS_EXCEPTION_HANDLER;
                    decltype(auto) usage = shelf.storage_usage;
                    decltype(auto) quota = shelf.storage_quota;
                    storage_estimate_t dictionary {{"usage", usage}, {"quota", quota}};

                    // if an exception was thrown from JavaScript when trying to access these members, then queue a task
                    // to reject the promise with a JavaScript TypeError
                    if (JS_EXCEPTION_HAS_THROWN)
                        dom::detail::queue_microtask(
                                [&promise]
                                {promise.set_exception();}); // TODO : JavaScript TypeError

                    // otherwise, queue a task to resolve the promise with the created 'dictionary'
                    else
                        dom::detail::queue_microtask(
                                [&promise, dictionary = std::move(dictionary)] mutable
                                {promise.set_value(std::move(dictionary));});
                });
    }

    // return the promise
    return promise;
}

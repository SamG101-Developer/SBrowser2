#include "idb_factory.hpp"

#include "ext/threading.ixx"

#include "dom/detail/event_internals.hpp"
#include "dom/detail/exception_internals.hpp"
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "indexed_db/idb_open_request.hpp"
#include "indexed_db/detail/algorithm_internals.hpp"
#include "indexed_db/detail/database_internals.hpp"
#include "indexed_db/detail/ecma_binding_internals.hpp"

#include "storage/detail/storage_internals.hpp"


auto indexed_db::idb_factory::open(
        const ext::string& name,
        ext::number<ulonglong> version)
        -> idb_open_request
{
    // throw a JavaScript type error if the version equals zero
    dom::detail::exception_internals::throw_v8_exception<V8_TYPE_ERROR>(
            [&version] {return version == 0;},
            "Version can not be 0");

    // get the storage key from the relevant global object (environment)
    JS_REALM_GET_RELEVANT(this);
    auto environment = this_relevant_global_object;
    auto storage_key = storage::detail::storage_internals::obtain_storage_key(environment);

    // throw a security error if the storage key is a failure, because the method cannot advance with a failed storage
    // key
    dom::detail::exception_internals::throw_v8_exception_formatted<SECURITY_ERR>(
            [&storage_key] {return !storage_key.has_value();},
            "Obtaining storage key failed", {}, {},
            P("Name", name),
            P("Version", version));

    // create a IDBOpenRequest and thread pool to execute the following lambda-steps in parallel (database connection
    // can be blocking)
    idb_open_request request;
    ext::thread_pool pool {1};

    pool.push_task(
            [&request, storage_key = std::move(*storage_key), name = std::move(name), version = std::move(version)]
    {
        // the result (connection or exception) is the result of opening a database (-connection), using the
        // 'storage_key', 'name', 'version', and a pointer to the 'request'
        auto result = detail::algorithm_internals::open_database(storage_key, name, version, &request);

        dom::detail::observer_internals::queue_microtask(
                [&request]
        {
            if (ext::holds_alternative<dom::other::dom_exception>(result))
            {
                // set the request's result to empty, the error to the exception from the attempt at opening the
                // database (-connection), the done flag to true, and fire an "error" event at the IDBOpenRequest
                // object, with specific "bubbles" and "cancelable" options set
                request.result = ext::any{};
                request.error = std::move(ext::get<dom::other::dom_exception>(result));
                request.m_done_flag = true;
                dom::detail::event_internals::fire_event("error", &request, {{"bubbles", true}, {"cancelable", true}});
            }

            else
            {
                // set the request's result to the connection from opening the database (-connection), the done flag
                // to true, and fire a "success" event at the IDBOpenRequest object, with no options set
                request.result = ext::get<detail::connection_t>(result);
                request.m_done_flag = true;
                dom::detail::event_internals::fire_event("success", &request);
            }
        });
    });

    return request;
}


auto indexed_db::idb_factory::delete_database(
        const ext::string& name)
        -> idb_open_request
{
    // get the storage key from the relevant global object (environment)
    JS_REALM_GET_RELEVANT(this);
    auto environment = this_relevant_global_object;
    auto storage_key = storage::detail::storage_internals::obtain_storage_key(environment);

    // throw a security error if the storage key is a failure, because the method cannot advance with a failed storage
    // key
    dom::detail::exception_internals::throw_v8_exception_formatted<SECURITY_ERR>(
            [&storage_key] {return !storage_key.has_value();},
            "Obtaining storage key failed", {}, {},
            P("Name", name));

    // create a IDBOpenRequest and thread pool to execute the following lambda-steps in parallel (database deletion can
    // be blocking)
    idb_open_request request;
    ext::thread_pool pool {1};

    pool.push_task(
            [&request, storage_key = std::move(*storage_key), name = std::move(name)]
    {
        // the result (database version or exception) is the result of deleting a database, using the 'storage_key',
        // 'name', and a pointer to the 'request'
        auto result = detail::algorithm_internals::delete_database(storage_key, name, &request);
        request.m_done_flag = true;

        dom::detail::observer_internals::queue_microtask(
                [&request, result = std::move(result)]
        {
            if (ext::holds_alternative<dom::other::dom_exception>(result))
            {
                // set the request's error to the exception from the attempt at deleting the database, the done flag to
                // true, and fire an "error" event at the IDBOpenRequest object, with specific "bubbles" and
                // "cancelable" options set
                request.error = std::move(ext::get<dom::other::dom_exception>(result));
                request.m_done_flag = true;
                dom::detail::event_internals::fire_event("error", &request, {{"bubbles", true}, {"cancelable", true}});
            }

            else
            {
                using detail::database_version_t;

                // set the request's result to empty, the done flag to true, and fire a "success" event at the
                // IDBOpenRequest object, with the "oldVersion" set to an empty number, and the "newVersion" set to the
                // result of deleting the database
                request.result = ext::any{};
                request.m_done_flag = true;
                dom::detail::event_internals::fire_event("success", &request, {{"oldVersion"}, {"newVersion", ext::get<database_version_t>(result)}});
            }
        });
    });
}


auto indexed_db::idb_factory::databases()
        -> ext::promise<ext::vector<ext::map<ext::string, ext::any>>>
{
    // get the storage key from the relevant global object (environment)
    JS_REALM_GET_RELEVANT(this);
    auto environment = this_relevant_global_object;
    auto storage_key = storage::detail::storage_internals::obtain_storage_key(environment);

    // throw a security error if the storage key is a failure, because the method cannot advance with a failed storage
    // key
    dom::detail::exception_internals::throw_v8_exception_formatted<SECURITY_ERR>(
            [&storage_key] {return !storage_key.has_value();},
            "Obtaining storage key failed");

    // create a promise object and thread pool to execute the following lambda-steps in parallel
    ext::promise<ext::vector<ext::map<ext::string, ext::any>>> promise;
    ext::thread_pool pool {1};

    pool.push_task(
            []
    {
        // TODO
    });

    return promise;
}


auto indexed_db::idb_factory::cmp(
        const ext::any& first,
        const ext::any& second)
        -> ext::number<short>
{
    // create an exception handler, as converting keys to values can throw JavaScript errors
    JS_EXCEPTION_HANDLER;

    // convert the first argument 'a'
    auto a = detail::ecma_binding_internals::convert_key_to_value(first.to<detail::any_key_t>());
    dom::detail::exception_internals::throw_v8_exception_formatted<DATA_ERR>(
            [&] {JS_EXCEPTION_HAS_THROWN;},
            "Invalid first argument (not convertible to a value", {}, {},
            P("First argument", first));

    // convert the second argument 'b'
    auto b = detail::ecma_binding_internals::convert_key_to_value(second.to<detail::any_key_t>());
    dom::detail::exception_internals::throw_v8_exception_formatted<DATA_ERR>(
            [&] {JS_EXCEPTION_HAS_THROWN;},
            "Invalid second argument (not convertible to a value", {}, {},
            P("Second argument", second));

    // return a comparison of the two records (containing the key and created value)
    return detail::database_internals::compare_two_keys(a, b);
}

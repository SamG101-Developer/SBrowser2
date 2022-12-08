#include "permissions.hpp"






#include "permissions/detail/permission_internals.hpp"
#include "permissions/permission_status.hpp"

#include <magic_enum.hpp>
#include <v8pp/convert.hpp>


auto permissions::permission::query(
        detail::permissions_descriptor_t&& permission_descriptor)
        -> ext::promise<permission_status*>
{
    auto e = js::env::env::relevant(this);
    if (v8pp::from_v8<dom::nodes::window*>(this_relevant_agent, this_relevant_global_object))
        ; // TODO : current settings object stuff

    // get the feature as a string and cast as the enum (leave in the optional state, as following behaviour relies on
    // the state of the `optional<feature_t>` type
    using permissions_policy::detail::feature_t;
    using permissions::detail::powerful_feature_t;

    auto feature_string = permission_descriptor[u"name"].to<powerful_feature_t>().name;
    auto feature = magic_enum::enum_cast<feature_t>(feature_string);

    // if the feature doesn't exist, then create a promise, reject it with a JavaScript TypeError, and return it - this
    // means that querying the permission has failed, so no state is returned in the promise, and an error is created in
    // the promise rejection
    if (!feature.has_value())
    {
        ext::promise<permission_status*> promise;
        promise.set_exception(nullptr); // TODO : JavaScript TypeError
        return promise;
    }

    // create a thread pool with one thread in, which will run the following lambda, handling the setting of a value
    // into the promise
    ext::thread_pool pool{1};
    ext::promise<permission_status*> promise;

    // push a task into the thread pool which creates a PermissionStatus object from the 'root_descriptor', extracts the
    // [[query]] slot value from it, and runs the associated 'permission_query_algorithm'. the PermissionStatus object
    // is set into the promise type
    pool.push_task(
            [&promise, root_descriptor = std::move(permission_descriptor)] mutable
            {
                permission_status status {std::move(root_descriptor)};
                auto query = status->d_func()->query;
                query[u"name"].to<powerful_feature_t>().permission_query_algorithm(std::move(query), &status);
                promise.set_value(&status);
            });

    // return the promise
    return promise;
}

#include "media_devices.hpp"

#include "ext/boolean.hpp"
#include "ext/threading.hpp"

#include "environment/realms_2.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/document_internals.hpp"

#include "mediacapture_main/detail/devices_internals.hpp"
#include "mediacapture_main/media_device_info.hpp"
#include "mediacapture_main/media_stream.hpp"

#include "permissions/detail/permission_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/map.hpp>


auto mediacapture::main::media_devices::enumerate_devices()
        -> std::promise<ext::vector<media_device_info*>>
{
    // create a promise object that will be returned
    std::promise<ext::vector<media_device_info*>> promise;

    // create a thread pool containing a single thread, to execute the following lambda in parallel
    ext::thread_pool pool{1};

    pool.push_task([this, &promise]
    {
        // get the associated document of the relevant global object, and then wait until enumeration can proceed; this
        // would require the Document to be fully active and focused, so these are the conditions that are being waited
        // on (this is why the steps are run in parallel, so it doesn't block other parts of the code)
        JS_REALM_GET_RELEVANT(this);
        auto* document = javascript::environment::realms_2::get<dom::nodes::document*>(this_relevant_global_object, "associated_document");
        while (!detail::devices_internals::device_enumeration_can_proceed()) continue;

        // get the current stored devices from the [[stored_devices_list]] slot on the relevant global object, and
        // create a MediaDeviceInfo list based on these MediaDevices. set the value of the promise<T> object to this
        // 'result_list'
        auto stored_device_list = javascript::environment::realms_2::get<ext::vector<main::media_devices*>>(this_relevant_global_object, "[[stored_device_list]]");
        auto result_list = detail::devices_internals::create_list_of_device_info_objects(stored_device_list, document);
        promise.set_value(result_list);
    });
}


auto mediacapture::main::media_devices::get_user_media(
        detail::constraints_t&& constraints)
        -> std::promise<media_stream*>
{
    // the 'requested_media_types' are the constraints' keys whose corresponding values are either [boolean and TRUE, or
    // a dictionary, converted into a set of strings
    auto requested_media_types = constraints
            | ranges::views::filter([](const ext::any& value) {return value.try_to<ext::map<ext::string, ext::any>>() || value.try_to<ext::boolean>() && value.to<ext::boolean>() == ext::boolean::TRUE_();})
            | ranges::views::keys
            | ranges::to<ext::set<ext::string>>;

    // get the associated document of the relevant global object
    JS_REALM_GET_RELEVANT(this);
    auto* document = javascript::environment::realms_2::get<dom::nodes::document*>(this_relevant_global_object, "associated_document");

    // if there are no 'requested_media_types' (no constraint values were true / dictionaries), then reject the promise
    // with a JavaScript TypeError and return it
    if (requested_media_types.empty())
    {
        std::promise<media_stream*> promise;
        promise.set_exception(/* TODO : JavaScript TypeError */);
        return promise;
    }

    // if the Document isn't fully active, then reject the promise with an "invalid_state_error" DOMException, and
    // return it
    if (!dom::detail::is_document_fully_active(document))
    {
        std::promise<media_stream*> promise;
        promise.set_exception(dom::other::dom_exception{"Document must be fully active", INVALID_STATE_ERROR});
        return promise;
    }

    // return the result of the permission_failure lambda if the 'requested_media_types' contains the "audio" or "video"
    // keyword, and the Document isn't allowed to use that feature
    return_if (ranges::contains(requested_media_types, "audio") && !html::detail::allowed_to_use(document, "audio")) permission_failure();
    return_if (ranges::contains(requested_media_types, "video") && !html::detail::allowed_to_use(document, "video")) permission_failure();

    ext::thread_pool pool{1};
    pool.push_task(
            [document, requested_media_types = std::move(requested_media_types)] mutable
            {
                while (!dom::detail::is_document_fully_active(document) /* TODO : and wait for Document to have focus */) continue;
                ext::set<ext::string> final_set;

                for (ext::string_view kind: requested_media_types)
                {
                    // TODO
                }

                media_stream stream;
                auto loop =
                        [requested_media_types = std::move(requested_media_types)](int, int)
                        {
                            for (ext::string_view kind: requested_media_types)
                            {
                                permissions::detail::permission_internals::request_permission_to_use({{"name", kind}});
                            }
                        };
                // TODO
            });
}

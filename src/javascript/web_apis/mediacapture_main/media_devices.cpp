#include "media_devices.hpp"

#include "dom/_typedefs.hpp"
#include "ext/boolean.hpp"
#include "ext/threading.hpp"

#include "javascript/environment/realms.hpp"

#include "dom/detail/exception_internals.hpp"
#include "dom/detail/node_internals.hpp"
#include "dom/nodes/document.hpp"
#include "dom/nodes/document_private.hpp"
#include "dom/nodes/window.hpp"
#include "dom/nodes/window_private.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/document_internals.hpp"

#include "mediacapture_main/detail/devices_internals.hpp"
#include "mediacapture_main/media_device_info.hpp"
#include "mediacapture_main/media_stream.hpp"

#include "permissions/detail/permission_internals.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"

#include <range/v3/algorithm/contains.hpp>
#include <range/v3/to_container.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/map.hpp>


auto mediacapture::main::media_devices::enumerate_devices() -> ext::promise<ext::vector<media_device_info*>>
{
    // create a promise object that will be returned
    ext::promise<ext::vector<media_device_info*>> promise;

    GO [this, &promise]
    {
        // get the associated document of the relevant global object, and then wait until enumeration can proceed; this
        // would require the Document to be fully active and focused, so these are the conditions that are being waited
        // on (this is why the steps are run in parallel, so it doesn't block other parts of the code)
        auto e = js::env::env::relevant(this);
        decltype(auto) document = e.cpp.global<dom::nodes::window*>()->d_func()->document.get();
        while (!detail::device_enumeration_can_proceed()) continue;

        // get the current stored devices from the [[stored_devices_list]] slot on the relevant global object, and
        // create a MediaDeviceInfo list based on these MediaDevices. set the value of the promise<T> object to this
        // 'result_list' TODO
        auto stored_device_list = js::env::realms::get<ext::vector<main::media_devices*>>(this_relevant_global_object, "[[stored_device_list]]"); // TODO
        auto result_list = detail::create_list_of_device_info_objects(stored_device_list, document);
        promise.resolve(result_list);
    };
}


auto mediacapture::main::media_devices::get_user_media(
        detail::constraints_t&& constraints)
        -> ext::promise<media_stream*>
{
    using enum dom::detail::dom_exception_error_t;

    // the 'requested_media_types' are the constraints' keys whose corresponding values are either [boolean and TRUE, or
    // a dictionary, converted into a set of strings
    auto requested_media_types = constraints
            | ranges::views::filter([](const ext::any& value) {return value.try_to<ext::map<ext::string, ext::any>>() || value.try_to<ext::boolean>() && value.to<ext::boolean>() == ext::boolean::TRUE_();})
            | ranges::views::keys
            | ranges::to<ext::set<ext::string>>;

    // get the associated document of the relevant global object
    auto e = js::env::env::relevant(this);
    auto* document = e.cpp.global<dom::nodes::window*>()->d_func()->document();

    // if there are no 'requested_media_types' (no constraint values were true / dictionaries), then reject the promise
    // with a JavaScript TypeError and return it
    if (requested_media_types.empty())
    {
        ext::promise<media_stream*> promise;
        promise.resolve(/* TODO : JavaScript TypeError */);
        return promise;
    }

    // if the Document isn't fully active, then reject the promise with an "invalid_state_error" DOMException, and
    // return it
    if (!dom::detail::is_document_fully_active(document))
    {
        ext::promise<media_stream*> promise;
        web_idl::detail::resolve_promise(promise, e.js.realm(), dom::other::dom_exception{u8"Document must be fully active", INVALID_STATE_ERR});
        return promise;
    }

    // return the result of the permission_failure lambda if the 'requested_media_types' contains the "audio" or "video"
    // keyword, and the Document isn't allowed to use that feature
    return_if (ranges::contains(requested_media_types, u"audio") && !html::detail::allowed_to_use(document, u"audio")) permission_failure();
    return_if (ranges::contains(requested_media_types, u"video") && !html::detail::allowed_to_use(document, u"video")) permission_failure();
    
    GO [document, requested_media_types = std::move(requested_media_types)] mutable
    {
        while (!dom::detail::is_document_fully_active(document) /* TODO : and wait for Document to have focus */) continue;
        ext::set<ext::string> final_set;

        for (ext::string_view kind: requested_media_types)
        {
            // TODO
        }

        media_stream stream;
        auto loop = [requested_media_types = std::move(requested_media_types)](int, int)
        {
            for (ext::string_view kind: requested_media_types)
                permissions::detail::request_permission_to_use({{u"name", kind}});
        };

        // TODO
    };
}

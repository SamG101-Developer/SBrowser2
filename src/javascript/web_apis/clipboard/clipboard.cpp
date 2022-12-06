#include "clipboard.hpp"




#include INCLUDE_INNER_TYPES(clipboard)
#include "clipboard/clipboard_item.hpp"
#include "clipboard/detail/clipboard_internals.hpp"

#include INCLUDE_INNER_TYPES(dom)
#include "dom/detail/observer_internals.hpp"
#include "dom/other/dom_exception.hpp"

#include "html/detail/task_internals.hpp"
#include "mimesniff/detail/mimetype_internals.hpp"

#include <range/v3/view/cache1.hpp>
#include <range/v3/view/map.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/take.hpp>
#include <range/v3/view/transform.hpp>


auto clipboard::clipboard::read()
        -> ext::promise<ext::vector<clipboard_item>>
{
    // Create a promise for returning, which will be resolved or rejected depending on the permission state and
    // clipboard access of the user agent.
    auto promise = ext::promise<ext::vector<clipboard_item>>{};

    // Run the following steps in parallel, because they can be blocking (there are calls to enqueue steps on different
    // task sources, such as retrieving the contents of the clipboard)
    GO [&promise]
    {
        // Check if the user agent is allowed to read from the clipboard (uses Permissions API internally)
        auto allowed_to_read = detail::check_clipboard_read_permission();

        // If the user agent isn't allowed to read from the clipboard, then queue a task on the permissions task source
        // to reject the 'promise', with a NOT_ALLOWED_ERR.
        return_if (!allowed_to_read) dom::detail::queue_task(html::detail::permissions_task_source,
                [&promise]
                {promise.reject(dom::other::dom_exception{"Permission to read clipboard denied", NOT_ALLOWED_ERR});});

        // Otherwise, the user agent is allowed to read from the clipboard, so queue a task on the clipboard task source
        // that resolved the promise with the clipboard data -- a transformation of the mime_type-data map to a list of
        // ClipboardItem objects.
        auto data = detail::system_clipboard_data();
        dom::detail::queue_task(html::detail::clipboard_task_source,
                [&promise, &data]
                {promise.resolve(data
                        | ranges::views::cache1
                        | ranges::views::transform_to_obj<clipboard_item>()
                        | ranges::to<ext::vector<clipboard_item>>);});
    };

    // Return the promise, while the above parallel method works on the promise.
    return promise;
}


auto clipboard::clipboard::read_text()
        -> ext::promise<ext::string>
{
    // Create a promise for returning, which will be resolved or rejected depending on the permission state and
    // clipboard access of the user agent.
    auto promise = ext::promise<ext::string>{};

    // Run the following steps in parallel, because they can be blocking (there are calls to enqueue steps on different
    // task sources, such as retrieving the contents of the clipboard)
    GO [&promise]
    {
        // Check if the user agent is allowed to read from the clipboard (uses Permissions API internally)
        auto allowed_to_read = detail::check_clipboard_read_permission();

        // If the user agent isn't allowed to read from the clipboard, then queue a task on the permissions task source
        // to reject the 'promise', with a NOT_ALLOWED_ERR.
        return_if (!allowed_to_read) dom::detail::queue_task(html::detail::permissions_task_source,
                 [&promise]
                 {promise.reject(dom::other::dom_exception{"Permission to read clipboard denied", NOT_ALLOWED_ERR});});

        // Otherwise, the user agent is allowed to read from the clipboard, so queue a task on the clipboard task source
        // that resolved the promise with the clipboard data -- a transformation of the mime_type-data map to a list of
        // ClipboardItem objects.
        auto data = detail::system_clipboard_data();
        dom::detail::queue_task(html::detail::clipboard_task_source, [&promise, &data]
        {
            auto item_type_list = data
                    | ranges::views::take(1)
                    | ranges::views::cache1
                    | ranges::views::transform_to_obj<clipboard_item>()
                    | ranges::views::transform_to_attr(&clipboard_item::m_clipboard_item)
                    | ranges::views::transform_to_attr(&detail::clipboard_item_t::list_of_representations)
                    | ranges::views::join
                    ;

            using enum ranges::views::filter_compare_t;
            for (auto& representation: item_type_list
                    | ranges::views::filter_eq<EQ>(&detail::representation_t::mime_type, "text/plain", mimesniff::detail::essence))

                // React to the 'promise' in different ways, depending on the 'mime_type'.
                promise.react([&promise]<typename T>(T&& value) mutable
                {
                    // Resolving a promise with T matching ext::string
                    if constexpr (type_is<T, ext::string, ext::string_view>)
                        promise.template resolve(std::forward<T>(value));

                        // Resolving a promise with T matching Blob
                    else if constexpr (type_is<T, file_api::blob*>)
                        promise.template resolve(value->s_byte_sequence());
                },

                [&promise]
                {
                    // Rejecting the promise: create a NOT_FOUND_ERR dom exception, and reject the promise with it.
                    promise.reject(std::move(dom::other::dom_exception{"Error", NOT_FOUND_ERR}));
                });

            promise.reject(std::move(dom::other::dom_exception{"Error", NOT_FOUND_ERR}));
            return promise;
        });
    };
}


auto clipboard::clipboard::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<clipboard>{isolate}
        .inherit<dom::nodes::event_target>()
        .function("read", &clipboard::read)
        .function("readText", &clipboard::read_text)
        .function("write", &clipboard::write)
        .function("writeText", &clipboard::write_text)
        .auto_wrap_objects();
}

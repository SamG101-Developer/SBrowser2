#include "navigator.hpp"

#include "ext/threading.hpp"

#include "dom/nodes/document.hpp"

#include "mediacapture_main/media_devices.hpp"

#include USE_INNER_TYPES(badging)


auto html::other::navigator::get_user_media(
        ext::map<ext::string, ext::any>&& constraints,
        html::other::navigator::navigator_user_media_success_callback&& success_callback,
        html::other::navigator::navigator_user_media_error_callback&& error_callback)
        const -> void
{
    auto promise = media_devices()->get_user_media(std::move(constraints));
    // TODO : call success_callback when std::promise set-value called
    // TODO : call error callback when std::promise set-error called
}


auto html::other::navigator::set_client_badge(
        ext::optional<ext::number<ulonglong>> contents)
        -> std::promise<void>
{
    // Run an algorithm in parallel that handles setting the badge of the Document.
    go [this, &contents]
    {
        JS_REALM_GET_RELEVANT(this);
        auto* document = javascript::environment::realms_2::get<dom::nodes::document*>(this_relevant_global_object, "responsible_document");
        document->m_badge = !contents.has_value()
                ? badging::detail::badge_value_t::FLAG : *contents == 0
                ? badging::detail::badge_value_t::NOTHING : std::move(*contents);
    };

    // Return a resolved std::promise<void> whilst the above code is executing in another thread.
    std::promise<void> promise;
    promise.set_value();
    return promise;
}


auto html::other::navigator::clear_client_badge()
        -> std::promise<void>
{
    go [this]
    {
        JS_REALM_GET_RELEVANT(this);
        auto* document = javascript::environment::realms_2::get<dom::nodes::document*>(this_relevant_global_object, "responsible_document");
        document->m_badge = badging::detail::badge_value_t::NOTHING;
    };

    // Return a resolved std::promise<void> whilst the above code is executing in another thread.
    std::promise<void> promise;
    promise.set_value();
    return promise;
}

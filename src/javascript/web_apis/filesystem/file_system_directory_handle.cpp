#include "file_system_directory_handle.hpp"
#include "file_system_directory_handle_private.hpp"

#include "ext/functional.ixx"
#include "ext/ranges.hpp"

#include "dom/_typedefs.hpp"
#include "dom/other/dom_exception.hpp"
#include "dom/detail/exception_internals.hpp"

#include "filesystem/detail/file_internals.hpp"
#include "filesystem/file_system_file_handle.hpp"
#include "filesystem/file_system_file_handle_private.hpp"

#include "file_system_file_handle.hpp"
#include "hr_time/detail/time_internals.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"


auto filesystem::file_system_directory_handle::get_directory_handle(
        ext::string_view name,
        detail::file_system_get_directory_options_t&& options)
        -> ext::promise<std::unique_ptr<file_system_directory_handle>>
{
    using enum v8_primitive_error_t;
    using enum dom::detail::dom_exception_error_t;
    auto e = js::env::env::relevant(this);

    auto result = web_idl::detail::create_promise<std::unique_ptr<file_system_directory_handle>>(e.js.realm());

    GO [this, name, &e, &result, options = std::move(options)] mutable
    {
        ACCESS_PIMPL(file_system_directory_handle);

        dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
                [name] {return !detail::is_valid_file_name(name);},
                u8"Invalid name", e);

        JS_EXCEPTION_HANDLER;
        auto access = d->entry->query_access(options[u"create"] ? detail::mode_t::READWRITE : detail::mode_t::READ);
        if (JS_EXCEPTION_HAS_THROWN)
            return web_idl::detail::reject_promise(result, e.js.realm(), JS_EXCEPTION);

        dom::detail::throw_v8_exception<NOT_ALLOWED_ERR>(
                [access] {return access != permissions::detail::permission_state_t::GRANTED;},
                u8"Access not granted");

        using enum ranges::filter_compare_t;
        d->entry->children
                | ranges::views::transform(ext::underlying)
                | ranges::views::filter_eq<EQ>(&detail::entry_t::name, name, ext::identity)
                | ranges::views::for_each_if(
                        BIND_NO_ARGS(dom_cast<detail::directory_entry_t>),
                        BIND_FRONT(web_idl::detail::reject_promise, e.js.realm(), dom::other::dom_exception{u8"", TYPE_MISMATCH_ERR}),
                        BIND_FRONT(web_idl::detail::resolve_promise, e.js.realm(), std::make_shared<file_system_directory_handle>())); // TODO : set entry to the child in the for_each

        if (!options[u"create"])
            return web_idl::detail::reject_promise(result, e.js.realm(), dom::other::dom_exception{u8"", NOT_FOUND_ERR});

        auto child = std::make_shared<detail::file_entry_t>();
        child->query_access = d->entry->query_access;
        child->request_access = d->entry->request_access;
        child->name = d->entry->name;
        child->binary_data = u8"";
        child->modification_timestamp = hr_time::detail::current_hr_time(e.js.global());
        d->entry->children.insert(child);

        // TODO : some error stuff

        auto file_handle = std::make_unique<file_system_file_handle>();
        file_handle->d_func()->entry = child;
        web_idl::detail::resolve_promise(result, e.js.realm(), std::move(file_handle));
    };

    return result;
}

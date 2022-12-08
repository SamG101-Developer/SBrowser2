#include "file_system_file_handle.hpp"
#include "file_system_file_handle_private.hpp"

#include "ext/filesystem.ixx"




#include "file_api/file.hpp"
#include "file_api/file_private.hpp"

#include "filesystem/_typedefs.hpp"
#include "filesystem/detail/file_internals.hpp"
#include "filesystem/file_system_writable_file_stream.hpp"
#include "filesystem/file_system_writable_file_stream_private.hpp"

#include "permissions/_typedefs.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"


auto filesystem::file_system_file_handle::get_file()
        -> ext::promise<std::unique_ptr<file_api::file>>
{
    ACCESS_PIMPL(file_system_file_handle);
    auto e = js::env::env::relevant(this);
    auto result = web_idl::detail::create_promise<std::unique_ptr<file_api::file>>(e.js.realm());

    GO [d, &e, &result]
    {
        using enum dom::detail::dom_exception_error_t;

        if (d->entry->query_access(detail::mode_t::READ) != permissions::detail::permission_state_t::GRANTED)
            web_idl::detail::reject_promise(result, e.js.realm(), dom::other::dom_exception{u8"Permission not granted", NOT_ALLOWED_ERR});

        auto f = std::make_unique<file_api::file>();
        f->d_func()->snapshot_state = d->entry->state;
        f->d_func()->byte_sequence = d->entry->binary_data;
        f->d_func()->name = d->entry->name;
        f->d_func()->last_modified = d->entry->modification_timestamp;
        f->d_func()->type = ext::filesystem::FilePath{d->entry->name}.extension();

        web_idl::detail::resolve_promise(result, e.js.realm(), std::move(f));
    };

    return result;
}


auto filesystem::file_system_file_handle::create_writable(
        detail::file_system_create_writable_options_t&& options)
        -> ext::promise<std::unique_ptr<file_system_writable_file_stream>>
{
    ACCESS_PIMPL(file_system_file_handle);
    auto e = js::env::env::relevant(this);
    auto result = web_idl::detail::create_promise<std::unique_ptr<file_system_writable_file_stream>>(e.js.realm());

    GO [d, &e, &result, options = std::move(options)]
    {
        using enum dom::detail::dom_exception_error_t;

        if (d->entry->query_access(detail::mode_t::READWRITE) != permissions::detail::permission_state_t::GRANTED)
            web_idl::detail::reject_promise(result, e.js.realm(), dom::other::dom_exception{u8"Permission not granted", NOT_ALLOWED_ERR});

        if (!detail::take_lock(detail::take_lock_t::SHARED, *d->entry))
            web_idl::detail::reject_promise(result, e.js.realm(), dom::other::dom_exception{u8"Can't take lock", NO_MODIFICATION_ALLOWED_ERR});

        auto stream = detail::create_filesystem_writable_stream(*d->entry, e);
        if (options[u"keepExistingData"])
            stream->d_func()->buffer = d->entry->binary_data;

        web_idl::detail::resolve_promise(result, e.js.realm(), std::move(stream));
    };

    return result;
}

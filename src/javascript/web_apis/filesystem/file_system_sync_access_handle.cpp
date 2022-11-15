#include "file_system_sync_access_handle.hpp"
#include "file_system_sync_access_handle_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "filesystem/detail/file_internals.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"


auto filesystem::file_system_sync_access_handle::read(
        ext::buffer_source& buffer,
        detail::file_system_read_write_options_t&& options)
        -> ext::number<ulonglong>
{
    ACCESS_PIMPL(file_system_sync_access_handle);
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->state == detail::file_state_t::CLOSED;},
            u8"File must not be closed");

    auto e = js::env::env::relevant(this);
    auto buffer_size = web_idl::detail::byte_length(buffer, e.js.realm());
    auto file_contents = ext::u8string_view{d->file->binary_data};
    auto file_size = file_contents.length();
    auto read_start = options[u"at"].to<ext::number<ulonglong>>();
    return_if (read_start > file_size) 0;

    auto read_end = ext::min(file_size, read_start + (buffer_size - 1));
    auto bytes = file_contents.substr(read_start, read_end - read_start);
    auto result = bytes.length();

    // TODO : error handling

    decltype(auto) array_buffer = web_idl::detail::viewed_buffer(ext::get<1>(buffer));
    web_idl::detail::write(bytes, array_buffer);
    return result;
}

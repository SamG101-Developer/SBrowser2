module;
#include "ext/macros/language_shorthand.hpp"
#include "ext/macros/pimpl.hpp"


module apis.filesystem.file_system_sync_access_handle;
import apis.filesystem.file_system_sync_access_handle_private;
import apis.filesystem.types;

import apis.dom.detail;
import apis.dom.types;

import apis.web_idl.detail;

import ext.core;
import ext.js;
import js.env.realms;
import js.env.module_type;


auto filesystem::file_system_sync_access_handle::read(
        ext::buffer_source& buffer,
        file_system_read_write_options_t&& options)
        -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->state == detail::file_state_t::CLOSED;},
            u8"File must not be closed", js::env::env::relevant(this));

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


auto filesystem::file_system_sync_access_handle::write(
        ext::buffer_source& buffer,
        file_system_read_write_options_t&& options)
        -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->state == detail::file_state_t::CLOSED;},
            u8"File must not be closed", js::env::env::relevant(this));

    auto e = js::env::env::relevant(this);
    auto write_position = options[u"at"].to<ext::number<ulonglong>>();
    auto file_contents = ext::u8string{d->file->binary_data}; // NOTE : delibarately not a view
    auto old_size = file_contents.length();
    auto buffer_size = web_idl::detail::byte_length(buffer, e.js.realm());

    file_contents += ext::u8string{char8_t(0x00), (write_position - old_size) * (write_position > old_size)};
    auto head = file_contents.substr(0, write_position);
    auto tail = file_contents.substr(ext::min(write_position + buffer_size, old_size));
    auto new_size = head.length() + buffer_size + tail.length();

    // TODO : storage quota check

    d->file->binary_data = head /* TODO + buffer's data */ + tail;
    // TODO : error handing

    return buffer_size;
}


auto filesystem::file_system_sync_access_handle::truncate(
        ext::number<ulonglong> new_size)
        -> void
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->state == detail::file_state_t::CLOSED;},
            u8"File must not be closed", js::env::env::relevant(this));

    auto file_contents = ext::u8string{d->file->binary_data}; // NOTE : delibarately not a view
    auto old_size = file_contents.length();

    if (new_size > old_size)
    {
        // TODO : Quota Check
        d->file->binary_data = file_contents + ext::u8string{char8_t(0x00), new_size - old_size};
        // TODO : Error Handling
    }

    else
    {
        d->file->binary_data = file_contents.substr(0, new_size);
    }
}


auto filesystem::file_system_sync_access_handle::get_size() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    using enum dom::detail::dom_exception_error_t;

    dom::detail::throw_v8_exception<INVALID_STATE_ERR>(
            [d] {return d->state == detail::file_state_t::CLOSED;},
            u8"File must not be closed", js::env::env::relevant(this));

    return d->file->binary_data.length();
}

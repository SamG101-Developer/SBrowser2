#include "file_system_writable_file_stream.hpp"
#include "file_system_writable_file_stream_private.hpp"

#include "streams/detail/writable_abstract_operations.hpp"
#include "streams/writable/writable_stream_default_writer.hpp"


auto filesystem::file_system_writable_file_stream::write(
        detail::file_system_write_chunk_type_t&& data)
        -> ext::promise<void>
{
    auto writer = streams::detail::get_writer(this);
    auto result = streams::detail::write_chunk(writer.get(), std::move(data));
    streams::detail::release(writer.get());
    return result;
}


auto filesystem::file_system_writable_file_stream::seek(
        ext::number<ulonglong> position)
        -> ext::promise<void>
{
    auto writer = streams::detail::get_writer(this);
    auto result = streams::detail::write_chunk(writer.get(), ext::map<ext::string, ext::any>{{u"type", u"seek"}, {u"position", position}});
    streams::detail::release(writer.get());
    return result;
}


auto filesystem::file_system_writable_file_stream::truncate(
        ext::number<ulonglong> size)
        -> ext::promise<void>
{
    auto writer = streams::detail::get_writer(this);
    auto result = streams::detail::write_chunk(writer.get(), ext::map<ext::string, ext::any>{{u"type", u"truncate"}, {u"size", size}});
    streams::detail::release(writer.get());
    return result;
}

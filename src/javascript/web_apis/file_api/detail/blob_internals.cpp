#include "blob_internals.hpp"

#include "ext/array_buffer.hpp"

#include "file_api/_typedefs.hpp"
#include "file_api/blob.hpp"
#include "file_api/blob_private.hpp"

#include "infra/detail/infra_strings_internals.hpp"
#include "streams/readable/readable_stream.hpp"
#include "web_idl/detail/type_mapping_internals.hpp"



auto file_api::detail::get_stream(
        file_api::blob* blob_object)
        -> streams::readable::readable_stream
{
    streams::readable::readable_stream stream;
    streams::detail::setup(&stream);
    // TODO
}


auto file_api::detail::process_blob_parts(
        ext::vector<detail::blob_part_t>&& parts,
        ext::map<ext::string, ext::any>&& options)
        -> ext::string
{
    ext::string bytes;

    for (decltype(auto) element: parts)
    {
        if (ext::holds_alternative<ext::string>(element))
        {
            decltype(auto) string = ext::get<ext::string>(element);
            if (options[u"endings"].to<endings_t>() == endings_t::NATIVE)
                string = convert_line_endings_to_native(string);
            bytes += string;
        }

        else if (ext::holds_alternative<ext::array_buffer>(element))
        {
            auto e = js::env::env::current();
            decltype(auto) buffer = ext::get<ext::array_buffer>(element);
            bytes += web_idl::detail::get_copy_of_bytes_in_buffer_source(buffer, e.js.realm());
        }

        else if (ext::holds_alternative<blob*>(element))
        {
            decltype(auto) buffer = ext::get<blob*>(element);
            bytes += buffer->d_func()->byte_sequence();
        }
    }

    return bytes;
}


auto file_api::detail::convert_line_endings_to_native(
        ext::string_view input)
        -> ext::string
{
    auto string = ext::string{input};
    auto native_line_ending = char(0x000a); // TODO

    decltype(auto) position = string.begin();
    auto result = infra::detail::collect_code_points_not_matching(string, position, char(0x000a), char(0x000d));

    while (position != string.end())
    {
        if (*position == 0x000d)
        {
            result += native_line_ending;
            ranges::advance(position, 1);
            ranges::advance(position, position != string.end() && *position == 0x000a);
        }

        else if (*position == 0x000a)
        {
            result += native_line_ending;
            ranges::advance(position, 1);
        }

        result += infra::detail::collect_code_points_not_matching(string, position, char(0x000a), char(0x000d));
    }

    return result;
}

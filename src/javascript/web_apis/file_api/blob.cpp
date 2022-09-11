#include "blob.hpp"

#include "ext/ranges.hpp"

#include "file_api/detail/blob_internals.hpp"

#include "streams/readable/readable_stream.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/iota.hpp>


file_api::blob::blob(
        ext::vector<detail::blob_part_t>&& blob_parts,
        ext::map<ext::string, ext::any>&& options)
        : s_byte_sequence{detail::process_blob_parts(std::move(blob_parts), std::move(options))}
        , size{s_byte_sequence().size()}
        , type{""}
{
    auto options_type = options.try_emplace("type", "").first->second.to<ext::string>();

    if (!options_type.empty())
    {
        if (ranges::contains_any(options_type, ranges::views::closed_iota(0x0020, 0x007e)))
            return;

        options_type |= ranges::actions::lowercase();
        type = std::move(options_type);
    }
}


auto file_api::blob::slice(
        ext::number<longlong> start,
        ext::number<longlong> end,
        ext::string_view content_type)
        -> blob
{
    auto relative_start = start % size();
    auto relative_end = end % size();
    auto span = ext::max((relative_end - relative_start), 0);

    auto relative_content_type = ext::string{content_type};
    if (!ranges::contains_any(content_type, ranges::views::closed_iota(0x0020, 0x007e)))
        relative_content_type |= ranges::actions::lowercase();

    blob blob{{s_byte_sequence().substr(*relative_start, *span)}};
    blob.size = span;
    blob.type = relative_content_type;
    return blob;
}


auto file_api::blob::stream()
        -> streams::readable::readable_stream
{
    return detail::get_stream(this);
}


auto file_api::blob::text()
        -> ext::promise<ext::string>
{
    auto stream = detail::get_stream(this);
    auto reader = streams::detail::get_reader(&stream);
    auto promise = streams::detail::read_all_bytes(&stream, &reader);
    // TODO : return transformation
}


auto file_api::blob::array_buffer()
        -> ext::promise<v8::Local<v8::ArrayBuffer>>
{
    auto stream = detail::get_stream(this);
    auto reader = streams::detail::get_reader(&stream);
    auto promise = streams::detail::read_all_bytes(&stream, &reader);
    // TODO : return transformation
}


auto file_api::blob::m_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean&& for_storage)
        -> void
{
    serialized.insert_or_assign("$SnapshotState", s_snapshot_state());
    serialized.insert_or_assign("$ByteSequence" , s_byte_sequence());
}


auto file_api::blob::m_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean&& for_storage)
        -> blob*
{
    s_snapshot_state = serialized.at("$SnapshotState").to<decltype(s_snapshot_state)::value_t>();
    s_byte_sequence  = serialized.at("$ByteSequence ").to<decltype(s_byte_sequence) ::value_t>();
    return this;
}

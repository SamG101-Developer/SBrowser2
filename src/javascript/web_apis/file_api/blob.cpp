#include "blob.hpp"
#include "blob_private.hpp"

#include "ext/pimpl.hpp"
#include "ext/ranges.hpp"

#include INCLUDE_INNER_TYPES(file_api)

#include "file_api/detail/blob_internals.hpp"
#include "streams/readable/readable_stream.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/iota.hpp>


file_api::blob::blob(
        ext::vector<detail::blob_part_t>&& blob_parts,
        detail::blob_property_bag_t&& options)
{
    INIT_PIMPL(blob);
    ACCESS_PIMPL(blob);

    d->byte_sequence = detail::process_blob_parts(std::move(blob_parts), std::move(options));
    d->type = u"";

    auto options_type = options[u"type"].to<ext::string>();

    if (!options_type.empty())
    {
        return_if (ranges::contains_any(options_type, ranges::views::closed_iota(0x0020, 0x007e)));
        d->type = options_type | ranges::views::lowercase | ranges::to<ext::string>;
    }
}


auto file_api::blob::slice(
        ext::number<longlong> start,
        ext::number<longlong> end,
        ext::string_view content_type)
        -> blob
{
    ACCESS_PIMPL(blob);

    auto relative_start = start % d->byte_sequence.size();
    auto relative_end = end % d->byte_sequence.size();
    auto span = ext::max((relative_end - relative_start), 0);

    auto relative_content_type = ext::string{content_type};
    if (!ranges::contains_any(content_type, ranges::views::closed_iota(0x0020, 0x007e)))
        relative_content_type |= ranges::actions::lowercase();

    auto blob_object = blob{{d->byte_sequence.substr(*relative_start, *span)}};
    blob_object->d_func()->type = relative_content_type;
    return blob_object;
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


auto file_api::blob::_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage) -> void
{
    ACCESS_PIMPL(blob);
    serialized.insert_or_assign(u"$SnapshotState", d->snapshot_state);
    serialized.insert_or_assign(u"$ByteSequence" , d->byte_sequence);
}


auto file_api::blob::_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> self_t*
{
    ACCESS_PIMPL(blob);
    d->snapshot_state = serialized.at(u"$SnapshotState").to<decltype(d->snapshot_state)>();
    d->byte_sequence  = serialized.at(u"$ByteSequence ").to<decltype(d->byte_sequence)>();
    return this;
}


auto file_api::blob::get_size() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL(const blob);
    return d->byte_sequence.size();
}


auto file_api::blob::get_type() const -> ext::string
{
    ACCESS_PIMPL(const blob);
    return d->type;
}


auto file_api::blob::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<blob>{isolate}
        .inherit<dom_object>()
        .ctor<ext::vector<detail::blob_part_t>&&, detail::blob_property_bag_t&&>()
        .function("slice", &blob::slice)
        .function("stream", &blob::stream)
        .function("text", &blob::text)
        .function("arrayBuffer", &blob::array_buffer)
        .property("size", &blob::get_size)
        .property("type", &blob::get_type)
        .auto_wrap_objects();

    return std::move(conversion);
}

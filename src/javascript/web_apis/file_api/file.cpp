#include "file.hpp"

#include "ext/date.hpp"
#include "ext/pimpl.hpp"
#include "ext/ranges.hpp"

#include INCLUDE_INNER_TYPES(hr_time)
#include "file_api/detail/blob_internals.hpp"
#include <range/v3/view/iota.hpp>


file_api::file::file(
        ext::vector<detail::blob_part_t>&& file_bits,
        ext::string&& file_name,
        detail::file_property_bag_t&& options)
{
    INIT_PIMPL(file);
    ACCESS_PIMPL(file);

    auto bytes = detail::process_blob_parts(std::move(file_bits), std::move(options));
    auto options_type = options.try_emplace("type", "").first->second.to<ext::string>();

    if (!ranges::contains_any(options_type, ranges::views::closed_iota(0x0020, 0x007e)))
        options_type |= ranges::actions::lowercase();

    auto options_date = options.contains("lastModified")
            ? options["lastModified"].to<hr_time::epoch_time_stamp>()
            : ext::now().timestamp();

    d->name = std::move(file_name);
    d->byte_sequence = std::move(bytes);
    d->type = std::move(options_type);
    d->last_modified = options_date;
}


auto file_api::file::_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> void
{
    ACCESS_PIMPL(file);
    serialized.insert_or_assign("$SnapshotState", d->snapshot_state);
    serialized.insert_or_assign("$ByteSequence", d->byte_sequence);
    serialized.insert_or_assign("$Name", d->name);
    serialized.insert_or_assign("$LastModified", d->last_modified);
}


auto file_api::file::_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> self_t*
{
    ACCESS_PIMPL(file);
    d->snapshot_state = serialized.at("$SnapshotState").to<decltype(d->snapshot_state)>();
    d->byte_sequence = serialized.at("$SnapshotState").to<decltype(d->byte_sequence)>();
    d->name = serialized.at("$SnapshotState").to<decltype(d->name)>();
    d->last_modified = serialized.at("$SnapshotState").to<decltype(d->last_modified)>();
}


auto file_api::file::get_name() const -> ext::string
{
    ACCESS_PIMPL(const file);
    return d->name;
}


auto file_api::file::get_last_modified() const -> ext::number<longlong>
{
    ACCESS_PIMPL(const file);
    return d->last_modified;
}


auto file_api::file::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<file>{isolate}
        .inherit<blob>()
        .ctor<ext::vector<detail::blob_part_t>&&, ext::string&&, detail::file_property_bag_t&&>()
        .property("name", &file::get_name)
        .property("lastModified", &file::get_last_modified)
        .auto_wrap_objects();

    return std::move(conversion);
}

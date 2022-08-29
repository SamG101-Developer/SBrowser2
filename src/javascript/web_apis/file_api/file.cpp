#include "file.hpp"

#include "ext/date.hpp"
#include "ext/ranges.hpp"

#include "file_api/detail/blob_internals.hpp"

#include USE_INNER_TYPES(high_resolution_time)

#include <range/v3/view/iota.hpp>


file_api::file::file(
        ext::vector<detail::blob_part_t>&& file_bits,
        ext::string&& file_name,
        detail::file_property_bag_t&& options)
        : name{std::move(file_name)} // TODO : tidy CTor
{
    auto bytes = detail::process_blob_parts(std::move(file_bits), std::move(options));

    auto options_type = options.try_emplace("type", "").first->second.to<ext::string>();
    if (!ranges::contains_any(options_type, ranges::views::closed_iota(0x0020, 0x007e)))
        options_type |= ranges::actions::lowercase();

    auto options_date = options.contains("lastModified")
            ? options["lastModified"].to<high_resolution_time::detail::epoch_time_stamp_t>()
            : ext::now().timestamp();

    s_byte_sequence = std::move(bytes);
    size = s_byte_sequence().size();
    type = std::move(options_type);
    last_modified = std::move(options_date);
}


auto file_api::file::m_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean&& for_storage)
        -> ext::string
{
    serialized.insert_or_assign("$SnapshotState", s_snapshot_state());
    serialized.insert_or_assign("$ByteSequence", s_byte_sequence());
    serialized.insert_or_assign("$Name", name());
    serialized.insert_or_assign("$LastModified", last_modified());
}


auto file_api::file::m_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean&& for_storage)
        -> file*
{
    s_snapshot_state = serialized.at("$SnapshotState").to<decltype(s_snapshot_state)::value_t>();
    s_byte_sequence  = serialized.at("$SnapshotState").to<decltype(s_byte_sequence)::value_t>();
    name             = serialized.at("$SnapshotState").to<decltype(name)::value_t>();
    last_modified    = serialized.at("$SnapshotState").to<decltype(last_modified)::value_t>();
}

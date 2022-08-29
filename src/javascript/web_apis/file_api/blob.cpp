#include "blob.hpp"

#include "ext/ranges.hpp"

#include "file_api/detail/blob_internals.hpp"

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
        if (ranges::any_of(options_type,
                [allowed = ranges::views::closed_iota(0x0020, 0x007e), options_type = std::move(options_type)](auto& character)
                {return ranges::contains(options_type, character);}))
            return;

        options_type |= ranges::actions::lowercase();
        type = std::move(options_type);
    }
}


auto file_api::blob::m_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean&& for_storage)
        -> ext::string
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

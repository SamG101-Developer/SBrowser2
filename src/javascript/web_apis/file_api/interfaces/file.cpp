module;
#include "ext/macros.hpp"

#include <range/v3/view/iota.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.file_api.file;
import apis.file_api.detail;
import apis.file_api.types;

import apis.hr_time.detail;
import apis.hr_time.types;

import ext.core
import js.env.module_type;
import js.env.realms;


file_api::file::file(
        ext::vector<detail::blob_part_t>&& file_bits,
        ext::string&& file_name,
        detail::file_property_bag_t&& options)
{
    INIT_PIMPL;

    auto bytes = detail::process_blob_parts(std::move(file_bits), std::move(options));
    auto options_type = options[u"type"].to<ext::string>();

    if (!ranges::contains_any(options_type, ranges::views::closed_iota(0x0020, 0x007e)))
        options_type |= ranges::actions::lowercase;

    auto e = js::env::env::relevant(this);
    auto options_date = options.contains(u"lastModified")
            ? options[u"lastModified"].to<hr_time::epoch_time_stamp>()
            : std::bit_cast<hr_time::epoch_time_stamp>(hr_time::detail::current_hr_time(e.js.global()));

    ACCESS_PIMPL;
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
    ACCESS_PIMPL;
    serialized.insert_or_assign(u"$SnapshotState", d->snapshot_state);
    serialized.insert_or_assign(u"$ByteSequence", d->byte_sequence);
    serialized.insert_or_assign(u"$Name", d->name);
    serialized.insert_or_assign(u"$LastModified", d->last_modified);
}


auto file_api::file::_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> this_t*
{
    ACCESS_PIMPL;
    d->snapshot_state = serialized.at(u"$SnapshotState").to<decltype(d->snapshot_state)>();
    d->byte_sequence = serialized.at(u"$SnapshotState").to<decltype(d->byte_sequence)>();
    d->name = serialized.at(u"$SnapshotState").to<decltype(d->name)>();
    d->last_modified = serialized.at(u"$SnapshotState").to<decltype(d->last_modified)>();
}


auto file_api::file::get_name() const -> ext::string
{
    ACCESS_PIMPL;
    return d->name;
}


auto file_api::file::get_last_modified() const -> ext::number<longlong>
{
    ACCESS_PIMPL;
    return d->last_modified;
}


auto file_api::file::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<blob>()
        .ctor<ext::vector<detail::blob_part_t>&&, ext::string&&, detail::file_property_bag_t&&>()
        .property("name", &file::get_name)
        .property("lastModified", &file::get_last_modified)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

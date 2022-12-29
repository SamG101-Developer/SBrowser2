module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"

#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/algorithm/contains.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/to_container.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.file_api.blob;
import apis.file_api.blob_private;
import apis.file_api.detail;
import apis.file_api.types;

import ext.core;

import js.env.module_type;
import js.env.realms;


file_api::blob::blob(
        ext::vector<detail::blob_part_t>&& blob_parts,
        detail::blob_property_bag_t&& options)
{
    INIT_PIMPL; ACCESS_PIMPL;

    // Set the byte sequence to the processed 'blob_parts', and set the type to the string conversion of the "type"
    // option. If the 'type' contains blacklisted characters, set the type to empty.
    d->byte_sequence = detail::process_blob_parts(std::move(blob_parts), std::move(options));
    d->type = options[u"type"].to<ext::string>() | ranges::views::lowercase | ranges::to<ext::string>;
    d->type = ranges::contains_any(d->type, ranges::views::closed_iota(0x0020, 0x007e)) ? u"" : d->type;
}


auto file_api::blob::slice(
        ext::number<longlong> start,
        ext::number<longlong> end,
        ext::string_view content_type)
        -> std::unique_ptr<blob>
{
    ACCESS_PIMPL;

    // Get the 'relative_[start|end]' by taking the modulo of [start|end] against the size of the 'byte_sequence'. The
    // 'span' is the maximum of the difference between the ['relative_start' -> 'relative_end'] and 0 (ie force a
    // negative slice length up to 0).
    auto relative_start = start % d->byte_sequence.size();
    auto relative_end = end % d->byte_sequence.size();
    auto span = ext::max((relative_end - relative_start), 0);

    auto relative_content_type = ext::string{content_type};
    if (!ranges::contains_any(content_type, ranges::views::closed_iota(0x0020, 0x007e)))
        relative_content_type |= ranges::actions::lowercase;

    auto blob_object = std::make_unique<blob>(d->byte_sequence.substr(relative_start, span));
    blob_object->d_func()->type = relative_content_type;
    return blob_object;
}


auto file_api::blob::stream()
        -> std::unique_ptr<streams::readable_stream>
{
    return detail::get_stream(this);
}


auto file_api::blob::text()
        -> ext::promise<ext::string>
{
    auto stream = detail::get_stream(this);
    auto reader = streams::detail::get_reader(stream.get());
    auto promise = streams::detail::read_all_bytes(reader.get());

    auto e = js::env::env::relevant(this); // TODO : env
    return web_idl::detail::upon_fulfillment(
            promise, e.js.realm(),
            []<typename ...Args>(Args&&... arguments) {ext::nth_variadic_value<0>(std::forward<Args>(arguments)...);});
}


auto file_api::blob::array_buffer()
        -> ext::promise<ext::array_buffer>
{
    auto stream = detail::get_stream(this);
    auto reader = streams::detail::get_reader(stream.get());
    auto promise = streams::detail::read_all_bytes(reader.get());
    // TODO : return transformation
}


auto file_api::blob::_serialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> void
{
    ACCESS_PIMPL;
    serialized.insert_or_assign(u"$SnapshotState", d->snapshot_state);
    serialized.insert_or_assign(u"$ByteSequence" , d->byte_sequence);
}


auto file_api::blob::_deserialize(
        ext::map<ext::string, ext::any>& serialized,
        ext::boolean for_storage)
        -> this_t*
{
    ACCESS_PIMPL;
    d->snapshot_state = serialized.at(u"$SnapshotState").to<decltype(d->snapshot_state)>();
    d->byte_sequence  = serialized.at(u"$ByteSequence ").to<decltype(d->byte_sequence)>();
    return this;
}


auto file_api::blob::get_size() const -> ext::number<ulonglong>
{
    ACCESS_PIMPL;
    return d->byte_sequence.size();
}


auto file_api::blob::get_type() const -> ext::string
{
    ACCESS_PIMPL;
    return d->type;
}


auto file_api::blob::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .ctor<ext::vector<detail::blob_part_t>&&, detail::blob_property_bag_t&&>()
        .function("slice", &blob::slice)
        .function("stream", &blob::stream)
        .function("text", &blob::text)
        .function("arrayBuffer", &blob::array_buffer)
        .property("size", &blob::get_size)
        .property("type", &blob::get_type)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

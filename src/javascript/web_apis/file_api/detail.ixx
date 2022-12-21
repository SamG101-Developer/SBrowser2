module;
#include <memory>
#include <swl/variant.hpp>


export module apis.file_api.detail;
import apis.file_api.types;
import apis.url.types;

import ext.core

namespace file_api {class blob;}
namespace file_api {class file_reader;}
namespace streams {class readable_stream;}


export namespace file_api::detail
{
    auto get_stream(blob* blob_object) -> std::unique_ptr<streams::readable_stream>;
    auto process_blob_parts(ext::vector<detail::blob_part_t>&& parts, ext::map<ext::string, ext::any>&& options) -> ext::string;
    auto convert_line_endings_to_native(ext::string_view input) -> ext::string;
    auto package_data(ext::string_view bytes, ext::string_view type, ext::string_view mime_type = u"", ext::string_view encoding_name = u"") -> ext::string;
    auto generate_new_blob_url() -> ext::string;
    auto add_entry_to_blob_url_store();
    auto remove_entry_to_blob_url_store();
    auto resolve_blob_url(const url::detail::url_t&) -> ext::boolean;
    auto read_operation(file_reader* file_reader, blob* blob, ext::string_view optional_encoding_name = u"") -> ext::promise<ext::string>;
    auto fire_progress_event(ext::string_view e, file_reader* file_reader) -> ext::boolean;
}

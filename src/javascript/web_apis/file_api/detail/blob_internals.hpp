#ifndef SBROWSER2_BLOB_INTERNALS_HPP
#define SBROWSER2_BLOB_INTERNALS_HPP


#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include USE_INNER_TYPES(url)

namespace file_api {class blob;}

namespace file_api::detail
{
    auto get_stream(
            blob& blob_object)
            -> streams::readable::readable_stream;

    auto process_blob_parts(
            ext::vector<typename blob::blob_part_t>,
            ext::map<ext::string, ext::any>&& options)
            -> ext::string;

    auto convert_line_endings_to_native(
            ext::string_view string)
            -> ext::string;

    auto package_data(
            ext::string_view bytes,
            ext::string_view type,
            ext::string_view mime_type = "",
            ext::string_view encoding_name = "")
            -> ext::string;

    auto generate_new_blob_url()
            -> ext::string;

    /* TODO */ auto add_entry_to_blob_url_store();
    /* TODO */ auto remove_entry_to_blob_url_store();

    auto resolve_blob_url(
            const url::detail::url_t&)
            -> ext::boolean;
}

#endif //SBROWSER2_BLOB_INTERNALS_HPP

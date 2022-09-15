#ifndef SBROWSER2_BLOB_INTERNALS_HPP
#define SBROWSER2_BLOB_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"

#include USE_INNER_TYPES(file_api)
#include USE_INNER_TYPES(url)

namespace file_api {class blob;}
namespace media::source {class media_source;}
namespace streams::readable {class readable_stream;}


namespace file_api::detail
{
    auto get_stream(
            blob* blob_object)
            -> streams::readable::readable_stream;

    auto process_blob_parts(
            ext::vector<detail::blob_part_t>&& parts,
            ext::map<ext::string, ext::any>&& options)
            -> ext::string;

    auto convert_line_endings_to_native(
            ext::string_view input)
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


struct file_api::detail::blob_url_entry_t
{
    ext::variant<blob*, media::source::media_source*> object;
    v8::Local<v8::Object> settings;
};


#endif //SBROWSER2_BLOB_INTERNALS_HPP

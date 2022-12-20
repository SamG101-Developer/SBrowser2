module;
#include <swl/variant.hpp>
#include <v8-forward.h>


export module apis.file_api.types;

import ext.any;
import ext.array_buffer;
import ext.map;
import ext.string;
import ext.variant;

namespace file_api {class blob;}
namespace media::source {class media_source;}


export namespace file_api::detail
{
    struct blob_url_entry_t;

    enum class endings_t {TRANSPARENT, NATIVE};
    enum class state_t {EMPTY, LOADING, DONE};

    using blob_url_store_t = ext::map<ext::string, blob_url_entry_t>;
    using blob_part_t = ext::variant<blob*, ext::string, ext::array_buffer>;
    using blob_property_bag_t = ext::map<ext::string, ext::any>;
    using file_property_bag_t = ext::map<ext::string, ext::any>;
    using result_t = ext::variant<ext::string, ext::array_buffer, ext::variant_monostate_t>;
}


struct file_api::detail::blob_url_entry_t
{
    ext::variant<blob*, media::source::media_source*> object;
    v8::Local<v8::Object> settings;
};


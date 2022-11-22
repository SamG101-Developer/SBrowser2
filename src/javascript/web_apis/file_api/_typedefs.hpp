#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API__TYPEDEFS_HPP

#include "ext/array_buffer.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/variant.hpp"
#include <v8-array-buffer.h>
#include <v8-forward.h>

namespace file_api {class blob;}

namespace file_api::detail
{
    struct blob_url_entry_t;

    enum class endings_t {TRANSPARENT, NATIVE};
    enum class state_t {EMPTY, LOADING, DONE};

    using blob_url_store_t = ext::map<ext::string, blob_url_entry_t>;
    using blob_part_t = ext::variant<blob*, ext::string, ext::array_buffer>;
    using blob_property_bag_t = ext::map<ext::string, ext::any>;
    using file_property_bag_t = ext::map<ext::string, ext::any>;
    using result_t = ext::variant<ext::string, v8::Local<v8::ArrayBuffer>, ext::variant_monostate_t>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API__TYPEDEFS_HPP

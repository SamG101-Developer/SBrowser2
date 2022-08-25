#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API__TYPEDEFS_HPP

#include "ext/map.hpp"
#include "ext/string.hpp"

namespace file_api::detail
{
    struct blob_url_entry_t;
    using blob_url_store_t = ext::map<ext::string, blob_url_entry_t>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_FILE_API__TYPEDEFS_HPP

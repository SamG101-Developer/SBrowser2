#ifndef SBROWSER2_FETCH_TYPEDEFS_HPP
#define SBROWSER2_FETCH_TYPEDEFS_HPP


#include "ext/map.hpp"
#include "ext/pair.hpp"
#include "ext/tuple.hpp"
#include "ext/type_traits.hpp"
#include "ext/variant.hpp"

#include <v8-array-buffer.h>
namespace fetch::detail::body_internals {struct internal_body;}
namespace fetch::detail::fetch_internals {struct connection;}
namespace file_api {class blob;}
namespace xhr {class form_data;}
namespace streams::readable {class readable_stream;}


namespace fetch
{
    // body related
    using body_with_tuple = ext::tuple<detail::body_internals::internal_body&, ext::string>;
    using xml_http_request_body_init_t = ext::variant<file_api::blob*, v8::ArrayBuffer, xhr::form_data*, ext::string>;
    using body_init_t = ext::extend_variant_t<xml_http_request_body_init_t, streams::readable::readable_stream*>;

    // connection related
    using network_partition_key_t = ext::pair<ext::string, ext::string>;
    using connection_pool = ext::map<network_partition_key_t, detail::fetch_internals::connection>;

    // header related
    using header_name_t = ext::string;
    using header_value_t = ext::string;
    using header_t = ext::pair<header_name_t, header_value_t>;

    using header_names_t = ext::vector<header_name_t>;
    using header_values_t = ext::vector<header_value_t>;
    using headers_t = ext::vector<header_t*>;

    enum class header_guard_t {IMMUTABLE, REQUEST, REQUEST_NO_CORS, RESPONSE, NONE};
}

#endif //SBROWSER2_FETCH_TYPEDEFS_HPP

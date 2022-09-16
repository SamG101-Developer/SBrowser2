#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_MEDIA_QUERY_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_MEDIA_QUERY_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include USE_INNER_TYPES(css/media_queries)

namespace css::detail
{
    auto compare_media_queries(
            const media_queries_t& m1,
            const media_queries_t& m2)
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_MEDIA_QUERY_INTERNALS_HPP

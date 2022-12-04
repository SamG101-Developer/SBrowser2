#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_MISCELLANEOUS_QUERY_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_MISCELLANEOUS_QUERY_INTERNALS_HPP



#include INCLUDE_INNER_TYPES(css/media_queries)

namespace dom::nodes {class processing_instruction;}


namespace css::detail
{
    auto compare_media_queries(
            const media_queries_t& m1,
            const media_queries_t& m2)
            -> ext::boolean;

    auto processing_instruction_prolog_steps(
            dom::nodes::processing_instruction* instruction)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSSOM_DETAIL_MISCELLANEOUS_QUERY_INTERNALS_HPP

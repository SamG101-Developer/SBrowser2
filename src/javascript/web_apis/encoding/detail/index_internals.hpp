#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_INDEX_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_INDEX_INTERNALS_HPP

#include "ext/string.hpp"


namespace encoding::detail
{
    auto index_gb18030_ranges_code_point(
            const ext::string::iterator& pointer)
            -> char;

    auto index_gb1030_ranges_pointer(
            char code_point)
            -> ext::string::iterator;

    auto index_shift_jis_pointer()
            -> void;

    auto index_big5_pointer(
            char code_point)
            -> ext::string::iterator;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_INDEX_INTERNALS_HPP

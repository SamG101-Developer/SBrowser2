#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_INDEX_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_INDEX_INTERNALS_HPP




namespace encoding::detail
{
    template <typename T>
    auto index_gb18030_ranges_code_point(
            typename T::iterator& pointer)
            -> typename T::value_type;

    template <typename T>
    auto index_gb1030_ranges_pointer(
            typename T::value_type code_point)
            -> ext::string::iterator&;

    auto index_shift_jis_pointer()
            -> void;

    template <typename T>
    auto index_big5_pointer(
            typename T::value_type code_point)
            -> typename T::iterator;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_ENCODING_DETAIL_INDEX_INTERNALS_HPP

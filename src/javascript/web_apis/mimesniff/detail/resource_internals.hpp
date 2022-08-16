#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_RESOURCE_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_RESOURCE_INTERNALS_HPP


#include "mimesniff/_typedefs.hpp"

namespace mimesniff::detail::resource_internals
{
    auto determine_computed_mime_type_of_resource(
            const resource_t& resource)
            -> mime_type_t;

    auto identify_resource_with_unknown_mime_type(
            const resource_t& mime_type)
            -> void;

    auto distinguish_if_resource_is_text_or_binary(
            const resource_t& resource)
            -> mime_type_t;

    auto distinguish_if_resource_is_feed_or_html(
            const resource_t& resource)
            -> mime_type_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MIMESNIFF_DETAIL_RESOURCE_INTERNALS_HPP

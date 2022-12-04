#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_IMAGE_RESOURCE_DETAIL_PROCESSING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_IMAGE_RESOURCE_DETAIL_PROCESSING_INTERNALS_HPP

#include "ext/expected.ixx"
#include "ext/keywords.ixx"
#include "ext/optional.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(image_resource)
#include INCLUDE_INNER_TYPES(mimesniff)
#include INCLUDE_INNER_TYPES(url)


namespace image_resource::detail
{
    auto external_label()
        -> ext::string;

    auto process_image_resource_from_api(
            image_resource_options_t&& image_resource)
            -> ext::expected<image_resource_t, ext::failure_t>;

    auto process_image_resource_from_json(
            v8::Local<v8::Map> json_object,
            const url::detail::url_t& base)
            -> ext::expected<image_resource_options_t, ext::failure_t>;

    auto fetching_image_resource(
            const image_resource_t& image,
            ext::optional<const fetch::detail::request_t&> request = ext::nullopt)
            -> fetch::detail::response_t;

    auto derive_accessible_name(
            const image_resource_t& image)
            -> ext::string;

    auto embedded_accessible_name(
            const image_resource_t& image)
            -> ext::string;
};


struct image_resource::detail::image_resource_t
{
    url::detail::url_t& src;
    mimesniff::detail::mime_type_t& type;
    ext::string sizes;
    ext::string label;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_IMAGE_RESOURCE_DETAIL_PROCESSING_INTERNALS_HPP

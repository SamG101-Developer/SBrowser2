#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_CANVAS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_CANVAS_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"

#include USE_INNER_TYPES(html)


namespace html::detail
{
    template <typename T>
    auto context_creation_algorithm(
            ext::map<ext::string, ext::any>&& options)
            -> T;

    auto set_bitmap_dimensions(
            const ext::number<int>& width,
            const ext::number<int>& height)
            -> void;
};


struct html::detail::image_bitmap_t
{
    ext::boolean origin_clean_flag = true;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_CANVAS_INTERNALS_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_HPP

#include "performance_timeline/performance_entry.hpp"
namespace largest_contentful_paint {class largest_contentful_paint;}

#include USE_INNER_TYPES(high_resolution_time)
namespace dom::nodes {class element;}


class largest_contentful_paint::largest_contentful_paint
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(largest_contentful_paint);
    largest_contentful_paint() = default;

public js_properties:
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> render_time;
    ext::property<high_resolution_time::detail::dom_high_res_time_stamp_t> load_time;
    ext::property<ext::number<ulong>> size;
    ext::property<ext::string> id;
    ext::property<ext::string> url;
    ext::property<std::unique_ptr<dom::nodes::element>> element;

public cpp_methods:
    auto to_json() const -> ext::string override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_HPP

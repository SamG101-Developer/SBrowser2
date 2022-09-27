#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "performance_timeline/performance_entry_private.hpp"

#include INCLUDE_INNER_TYPES(hr_time)
namespace dom::nodes {class element;}


DEFINE_PRIVATE_CLASS(largest_contentful_paint, largest_contentful_paint) : performance_timeline::performance_entry_private
{
    hr_time::dom_high_res_time_stamp render_time = 0;
    hr_time::dom_high_res_time_stamp   load_time = 0;

    ext::number<ulong> size;
    ext::string id;
    ext::string url;

    dom::nodes::element* element;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_PRIVATE_HPP

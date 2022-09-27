#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_HPP

#include "performance_timeline/performance_entry.hpp"
namespace largest_contentful_paint {class largest_contentful_paint;}

#include INCLUDE_INNER_TYPES(hr_time)
namespace dom::nodes {class element;}

#include "largest_contentful_paint_private.hpp"


class largest_contentful_paint::largest_contentful_paint
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(largest_contentful_paint);
    MAKE_PIMPL(largest_contentful_paint);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(render_time, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(load_time, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(size, ext::number<ulong>);
    DEFINE_GETTER(id, ext::string);
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(element, dom::nodes::element*);

    DEFINE_GETTER(name, ext::string) override;
    DEFINE_GETTER(entry_type, ext::string) override;
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_LARGEST_CONTENTFUL_PAINT_LARGEST_CONTENTFUL_PAINT_HPP

module;
#include "ext/macros/pimpl.hpp"


export module apis.largest_contentful_paint.largest_contentful_paint_private;
import apis.performance_timeline.performance_entry_private;

import apis.dom.types;
import apis.hr_time.types;
import ext.core;


DEFINE_PRIVATE_CLASS(largest_contentful_paint, largest_contentful_paint)
        : performance_timeline::performance_entry_private
{
    hr_time::dom_high_res_time_stamp render_time = 0;
    hr_time::dom_high_res_time_stamp   load_time = 0;

    ext::number<ulong> size;
    ext::string id;
    ext::string url;

    std::observer_ptr<dom::element> element;
};

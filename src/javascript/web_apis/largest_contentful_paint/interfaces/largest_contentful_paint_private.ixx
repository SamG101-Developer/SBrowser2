module;
#include "ext/macros.hpp"


export module apis.largest_contentful_paint.largest_contentful_paint:p;
import apis.performance_timeline.performance_entry;

IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(hr_time);


DEFINE_PRIVATE_CLASS(largest_contentful_paint, largest_contentful_paint)
        : performance_timeline::performance_entry_private
{
public:
    MAKE_QIMPL(largest_contentful_paint);

public:
    hr_time::dom_high_res_time_stamp render_time = 0;
    hr_time::dom_high_res_time_stamp   load_time = 0;

    ext::number<ulong> size;
    ext::string id;
    ext::string url;

    std::observer_ptr<dom::element> element;
};

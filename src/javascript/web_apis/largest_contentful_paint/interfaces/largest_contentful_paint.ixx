module;
#include "ext/macros.hpp"


export module apis.largest_contentful_paint.largest_contentful_paint;
import apis.performance_timeline.performance_entry;

IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(hr_time);


DEFINE_PUBLIC_CLASS(largest_contentful_paint, largest_contentful_paint) final
        : public performance_timeline::performance_entry
{
public constructors:
    MAKE_PIMPL(largest_contentful_paint);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(render_time, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(load_time, hr_time::dom_high_res_time_stamp);
    DEFINE_GETTER(size, ext::number<ulong>);
    DEFINE_GETTER(id, ext::string);
    DEFINE_GETTER(url, ext::string);
    DEFINE_GETTER(element, dom::element*);

    DEFINE_GETTER(name, ext::string_view) override;
    DEFINE_GETTER(entry_type, ext::string_view) override;
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override;
};

#include "largest_contentful_paint.hpp"
#include "largest_contentful_paint_private.hpp"

#include "performance_timeline/performance_entry.hpp"


largest_contentful_paint::largest_contentful_paint::largest_contentful_paint()
{
    INIT_PIMPL(largest_contentful_paint);
}


auto largest_contentful_paint::largest_contentful_paint::get_render_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const largest_contentful_paint);
    return d->render_time;
}


auto largest_contentful_paint::largest_contentful_paint::get_load_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const largest_contentful_paint);
    return d->load_time;
}


auto largest_contentful_paint::largest_contentful_paint::get_size() const -> ext::number<ulong>
{
    ACCESS_PIMPL(const largest_contentful_paint);
    return d->size;
}


auto largest_contentful_paint::largest_contentful_paint::get_id() const -> ext::string
{
    ACCESS_PIMPL(const largest_contentful_paint);
    return d->id;
}


auto largest_contentful_paint::largest_contentful_paint::get_url() const -> ext::string
{
    ACCESS_PIMPL(const largest_contentful_paint);
    return d->url;
}


auto largest_contentful_paint::largest_contentful_paint::get_element() const -> dom::nodes::element*
{
    ACCESS_PIMPL(const largest_contentful_paint);
    return element_timing::get_element(d->element, nullptr);
}


auto largest_contentful_paint::largest_contentful_paint::get_name() const -> ext::string
{
    return "";
}


auto largest_contentful_paint::largest_contentful_paint::get_entry_type() const -> ext::string
{
    return "largest-contentful-paint";
}


auto largest_contentful_paint::largest_contentful_paint::get_start_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const largest_contentful_paint);
    return d->render_time ?: d->load_time;
}


auto largest_contentful_paint::largest_contentful_paint::get_duration() const -> hr_time::dom_high_res_time_stamp
{
    return 0;
}


auto largest_contentful_paint::largest_contentful_paint::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<largest_contentful_paint>{isolate}
        .inherit<performance_timeline::performance_entry>()
        .property("renderTime", &largest_contentful_paint::get_render_time)
        .property("loadTime", &largest_contentful_paint::get_load_time)
        .property("size", &largest_contentful_paint::get_size)
        .property("id", &largest_contentful_paint::get_id)
        .property("url", &largest_contentful_paint::get_url)
        .property("element", &largest_contentful_paint::get_element)
        .function("toJSON", &largest_contentful_paint::operator ext::string)
        .auto_wrap_objects();

    return std::move(conversion);
}

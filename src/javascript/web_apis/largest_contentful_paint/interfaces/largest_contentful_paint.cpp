module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"


module apis.largest_contentful_paint.largest_contentful_paint;
import apis.largest_contentful_paint.largest_contentful_paint_private;

import apis.dom.element;
import apis.hr_time.types;

import ext.core;
import js.env.module_type;


largest_contentful_paint::largest_contentful_paint::largest_contentful_paint()
{
    INIT_PIMPL;
}


auto largest_contentful_paint::largest_contentful_paint::get_render_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return d->render_time;
}


auto largest_contentful_paint::largest_contentful_paint::get_load_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return d->load_time;
}


auto largest_contentful_paint::largest_contentful_paint::get_size() const -> ext::number<ulong>
{
    ACCESS_PIMPL;
    return d->size;
}


auto largest_contentful_paint::largest_contentful_paint::get_id() const -> ext::string
{
    ACCESS_PIMPL;
    return d->id;
}


auto largest_contentful_paint::largest_contentful_paint::get_url() const -> ext::string
{
    ACCESS_PIMPL;
    return d->url;
}


auto largest_contentful_paint::largest_contentful_paint::get_element() const -> dom::element*
{
    ACCESS_PIMPL;
    return element_timing::get_element(d->element.get(), nullptr);
}


auto largest_contentful_paint::largest_contentful_paint::get_name() const -> ext::string_view
{
    return u"";
}


auto largest_contentful_paint::largest_contentful_paint::get_entry_type() const -> ext::string_view
{
    return u"largest-contentful-paint";
}


auto largest_contentful_paint::largest_contentful_paint::get_start_time() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL;
    return d->render_time ?: d->load_time;
}


auto largest_contentful_paint::largest_contentful_paint::get_duration() const -> hr_time::dom_high_res_time_stamp
{
    return 0;
}


auto largest_contentful_paint::largest_contentful_paint::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<performance_timeline::performance_entry>()
        .property("renderTime", &largest_contentful_paint::get_render_time)
        .property("loadTime", &largest_contentful_paint::get_load_time)
        .property("size", &largest_contentful_paint::get_size)
        .property("id", &largest_contentful_paint::get_id)
        .property("url", &largest_contentful_paint::get_url)
        .property("element", &largest_contentful_paint::get_element)
        .function("toJSON", &largest_contentful_paint::operator ext::string)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

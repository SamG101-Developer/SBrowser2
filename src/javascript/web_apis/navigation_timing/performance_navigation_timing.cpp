#include "performance_navigation_timing.hpp"

#include "html/detail/document_internals.hpp"


auto navigation_timing::performance_navigation_timing::get_unload_event_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->previous_document_unload_timing->unload_event_start_time;
}


auto navigation_timing::performance_navigation_timing::get_unload_event_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->previous_document_unload_timing->unload_event_unload_time; // TODO : check attribute
}


auto navigation_timing::performance_navigation_timing::get_dom_interactive() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->document_load_timing->dom_interactive_time;
}


auto navigation_timing::performance_navigation_timing::get_dom_content_loaded_event_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->document_load_timing->dom_content_loaded_event_start_time;
}


auto navigation_timing::performance_navigation_timing::get_dom_content_loaded_event_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->document_load_timing->dom_content_loaded_event_end_time;
}


auto navigation_timing::performance_navigation_timing::get_dom_complete() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->document_load_timing->dom_complete_time;
}


auto navigation_timing::performance_navigation_timing::get_load_event_start() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->document_load_timing->dom_content_loaded_event_start_time;
}


auto navigation_timing::performance_navigation_timing::get_load_event_end() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->document_load_timing->dom_content_loaded_event_end_time;
}


auto navigation_timing::performance_navigation_timing::get_type() const -> detail::navigation_timing_type_t
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->navigation_type;
}


auto navigation_timing::performance_navigation_timing::get_redirect_count() const -> ext::number<ushort>
{
    ACCESS_PIMPL(const performance_navigation_timing);
    return d->redirect_count;
}

#include "performance_server_timing.hpp"
#include "performance_server_timing_private.hpp"

#include "hr_time/_typedefs.hpp"


auto server_timing::performance_server_timing::get_name() const -> ext::string_view
{
    ACCESS_PIMPL(const performance_server_timing);
    return d->metric_name;
}


auto server_timing::performance_server_timing::get_duration() const -> hr_time::dom_high_res_time_stamp
{
    ACCESS_PIMPL(const performance_server_timing);
    return d->params.at(u8"dur").to<hr_time::dom_high_res_time_stamp>();
}

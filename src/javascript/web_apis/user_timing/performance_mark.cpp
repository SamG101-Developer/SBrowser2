#include "performance_mark.hpp"
#include "performance_mark_private.hpp"




#include "hr_time/detail/time_internals.hpp"


user_timing::performance_mark::performance_mark(
        ext::string&& mark_name,
        detail::performance_mark_options&& mark_options)
{
    INIT_PIMPL(performance_mark);
    ACCESS_PIMPL(performance_mark);

    auto e = js::env::env::current();
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&mark_options] {return mark_options[u"startTime"].to<decltype(d->start_time)>() < 0;},
            u8"Start time must be >= 0");

    d->name = std::move(mark_name);
    d->entry_type = u"mark";
    d->start_time = mark_options[u"startTime", hr_time::detail::current_hr_time(e.js.global())].to<hr_time::dom_high_res_time_stamp>();
    d->duration = 0;

    d->detail = mark_options[u"detail"]; // TODO : .to<ext::any>(); TODO : structured serialize
}


auto user_timing::performance_mark::get_detail() const -> ext::any
{
    ACCESS_PIMPL(const performance_mark);
    return d->detail;
}

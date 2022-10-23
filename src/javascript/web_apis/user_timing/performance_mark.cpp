#include "performance_mark.hpp"
#include "performance_mark_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/detail/exception_internals.hpp"

#include "hr_time/detail/time_internals.hpp"


user_timing::performance_mark::performance_mark(
        ext::string&& mark_name,
        detail::performance_mark_options&& mark_options)
{
    INIT_PIMPL(performance_mark);
    ACCESS_PIMPL(performance_mark);

    JS_REALM_GET_CURRENT;
    using enum v8_primitive_error_t;

    dom::detail::throw_v8_exception<V8_TYPE_ERROR>(
            [&mark_options] {return mark_options[u8"startTime"].to<decltype(d->start_time)>() < 0;},
            u8"Start time must be >= 0");

    d->name = std::move(mark_name);
    d->entry_type = u8"mark";
    d->start_time = mark_options.try_emplace("startTime", hr_time::detail::current_hr_time(current_global_object)).to<hr_time::dom_high_res_time_stamp>();
    d->duration = 0;

    d->detail = mark_options[u8"detail"]; // TODO : .to<ext::any>(); TODO : structured serialize
}


auto user_timing::performance_mark::get_detail() const -> ext::any
{
    ACCESS_PIMPL(const performance_mark);
    return d->detail;
}

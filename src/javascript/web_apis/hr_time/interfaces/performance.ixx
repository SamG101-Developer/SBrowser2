module;
#include "ext/macros.hpp"


export module apis.hr_time.performance;
import apis.dom.event_target;

IMPORT_ALL_TYPES(hr_time);


DEFINE_PUBLIC_CLASS(hr_time, performance)
        : public dom::event_target
{
public constructors:
    performance();
    MAKE_PIMPL(performance);
    MAKE_V8_AVAILABLE(ALL);

private js_methods:
    /* [HR-TIME] */
    auto now() const -> dom_high_res_time_stamp;

    /* [PERFORMANCE-TIMELINE] */
    auto get_entries() -> ext::vector<performance_timeline::performance_entry*>;
    auto get_entries_by_type(ext::string_view type) -> ext::vector<performance_timeline::performance_entry*>;
    auto get_entries_by_name(ext::string_view name, ext::string_view type = u"") -> ext::vector<performance_timeline::performance_entry*>;

    /* [RESOURCE-TIMING] */
    auto clear_resource_timings() -> void;
    auto set_resource_timing_buffer_size(ext::number<ulong> max_size) -> void;

    /* [USER-TIMING] */
    auto mark(ext::string&& mark_name, user_timing::detail::performance_mark_options_t&& mar_options = {}) -> user_timing::performance_mark;
    auto measure(ext::string&& measure_name, user_timing::detail::performance_measure_options_t&& measure_options = {}) -> user_timing::performance_measure;
    auto measure(ext::string&& measure_name, ext::string&& mark_start, ext::string&& mark_end) -> user_timing::performance_measure;
    auto clear_marks(ext::string&& mark_name) -> void;
    auto clear_measures(ext::string&& measure_name) -> void;

private js_properties:
    /* [HR-TIME] */
    DEFINE_GETTER(time_origin, ext::number<double>);

    /* [EVENT-TIMING] */
    DEFINE_GETTER(event_counts, event_timing::event_counts*);
    DEFINE_GETTER(interaction_counts, event_timing::interaction_counts*);
};


// TODO : `ext::property<Performance> performance` in `WindowOrWorkerGlobalScope`


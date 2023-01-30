module;
#include "ext/macros.hpp"
#include <function2/function2.hpp>


export module apis.html.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(html)
{
    class html_element;
    class html_iframe_element;
    class html_image_element;
    class html_slot_element;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(html)
{
    // [2.1.1] - Parallelism
    struct parallel_queue_t;

    // [2.3.5] - Dates & Times
    using year_t = ext::string;
    using month_t = ext::string;
    using week_t = ext::string;
    using day_t = ext::string;
    using date_t = ext::string;
    using yearless_date_t = ext::string;
    using time_t = ext::string;
    using local_date_and_time_t = ext::string;
    using time_zone_offset_t = ext::string;
    using global_date_and_time_t = ext::string;
    using duration_t = ext::string;

    // [2.3.6] - Colors
    using simple_color_t = ext::tuple<ext::number<char>, ext::number<char>, ext::number<char>>;

    // [2.3.7 / 2.3.8] - Space-Separated Tokens / Comma-Separated Tokens
    using space_separated_tokens_t = ext::string;
    using comma_separated_tokens_t = ext::string;

    // [2.3.11] - Unique Internal Values
    using unique_internal_value_t = ext::string;

    // [2.5] - Fetching Resources
    enum class cors_setting_attribute_t {ANONYMOUS, USE_CREDENTIALS};
    enum class lazy_loading_attribute_t {LAZY, EAGER};
    enum class blocking_attribute_t {RENDER};
    using lazy_loading_steps_t = ext::function<void()>;
}


struct html::detail::parallel_queue_t
{
    ext::queue<ext::function<auto()>> algorithm_queue;
};

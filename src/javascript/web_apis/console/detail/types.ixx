module;
#include "ext/macros.hpp"


export module apis.console.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(console)
{
    class console;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(console)
{
    enum class log_level_t {ASSERT_, DEBUG, ERROR, INFO, LOG, WARN};
    enum class print_type_t {TRACE, DIR};
    enum class count_type_t {COUNT, COUNT_RESET};
    enum class group_type_t {GROUP, GROUP_COLLAPSED};
    enum class timer_type_t {TIME_LOG, TIME_END};

    struct group_t;
}


struct console::detail::group_t
{
    ext::string label;
};

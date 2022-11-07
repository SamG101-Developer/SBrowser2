#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE__TYPEDEFS_HPP

namespace console::detail
{
    enum class log_level_t {ASSERT_, DEBUG, ERROR, INFO, LOG, WARN};
    enum class print_type_t {TRACE, DIR};
    enum class count_type_t {COUNT, COUNT_RESET};
    enum class group_type_t {GROUP, GROUP_COLLAPSED};
    enum class timer_type_t {TIME_LOG, TIME_END};

    struct group_t;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE__TYPEDEFS_HPP

#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_DETAIL_ABSTRACT_OPERATIONS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_DETAIL_ABSTRACT_OPERATIONS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(console)

namespace console::detail
{
    template <typename ...Args>
    auto logger(
            log_level_t log_level,
            Args&&... args)
            -> void;

    template <typename ...Args>
    auto formatter(
            Args&&... args)
            -> ext::string;

    template <typename ...Args>
    auto printer(
            print_type_t format_type,
            Args&&... data)
            -> void;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_DETAIL_ABSTRACT_OPERATIONS_HPP

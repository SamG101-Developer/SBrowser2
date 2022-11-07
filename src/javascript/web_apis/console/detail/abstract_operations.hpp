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

    template <ext::type_is_enum E, typename ...Args>
    auto printer(
            E format_type,
            Args&&... data)
            -> void;
}


struct console::detail::group_t
{
    ext::string label;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_DETAIL_ABSTRACT_OPERATIONS_HPP

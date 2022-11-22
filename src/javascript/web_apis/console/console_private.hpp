#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(console)
#include INCLUDE_INNER_TYPES(hr_time)
#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/number.hpp"
#include "ext/stack.hpp"
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(console, console)
        : virtual dom_object_private
{
    MAKE_QIMPL(console);

    ext::stack<std::unique_ptr<detail::group_t>> group_stack;
    ext::map<ext::any, ext::number<size_t>> count_map;
    ext::map<ext::string, hr_time::dom_high_res_time_stamp> timer_table;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_PRIVATE_HPP

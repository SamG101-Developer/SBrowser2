module;
#include "ext/macros/pimpl.hpp"


export module apis.console.console_private;
import apis.dom_object_private;
import apis.console.types;
import apis.hr_time.types;

import ext.any;
import ext.map;
import ext.number;
import ext.stack;
import ext.string;


DEFINE_PRIVATE_CLASS(console, console)
        : virtual dom_object_private
{
    MAKE_QIMPL(console);

    ext::stack<std::unique_ptr<detail::group_t>> group_stack;
    ext::map<ext::any, ext::number<size_t>> count_map;
    ext::map<ext::string, hr_time::dom_high_res_time_stamp> timer_table;
};

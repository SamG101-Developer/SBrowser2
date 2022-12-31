module;
#include "ext/macros.hpp"


export module apis.console.console:p;
import apis.dom_object;

IMPORT_ALL_TYPES(console);
IMPORT_ALL_TYPES(hr_time);
import ext.core;


DEFINE_PRIVATE_CLASS(console, console)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(console);

public:
    ext::stack<std::unique_ptr<detail::group_t>> group_stack;
    ext::map<ext::any, ext::number<size_t>> count_map;
    ext::map<ext::string, hr_time::dom_high_res_time_stamp> timer_table;
};

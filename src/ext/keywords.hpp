#pragma once
#ifndef SBROWSER2_KEYWORDS_HPP
#define SBROWSER2_KEYWORDS_HPP

#include <ext/detail/hash.hpp>

#define _T true
#define _F false

#define try try
#define catch_all catch (...)
#define catch_specific (exception_t) catch(const exception_t& exception)
#define catch_other catch (...)

#define string_switch(string) switch(ext::hash(string))
#define string_case(string) case(ext::hash(string))
#define string_default default

#define friends
#define aliases
#define enums
#define constructors

#define js_static_constants
#define js_methods
#define js_properties
#define js_slot_methods
#define js_slots

#define cpp_static_methods
#define cpp_methods
#define cpp_properties
#define cpp_accessors
#define cpp_operators
#define cpp_nested_classes

#define return_if(condition) if (condition) return
#define break_if(condition) if (condition) break
#define continue_if(condition) if (condition) continue


#endif //SBROWSER2_KEYWORDS_HPP

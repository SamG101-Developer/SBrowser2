#pragma once
#ifndef SBROWSER2_KEYWORDS_HPP
#define SBROWSER2_KEYWORDS_HPP

#include <ext/detail/hash.hpp>

#define _T true
#define _F false

#define try try
#define catch_all catch (...&)
#define catch_specific (exception_t) catch(const exception_t& exception)
#define catch_other catch (...&)

#define string_switch(string) switch(ext::detail::hash(string))
#define string_case(string) case(ext::detail::hash(string))
#define string_default default

#define JS_BLOCK_ENTER {
#define JS_BLOCK_EXIT }


#define enforce_range /* throw an error if the number is out of range */

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


#endif //SBROWSER2_KEYWORDS_HPP

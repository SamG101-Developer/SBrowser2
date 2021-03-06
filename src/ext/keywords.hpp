#pragma once
#ifndef SBROWSER2_KEYWORDS_HPP
#define SBROWSER2_KEYWORDS_HPP

#define _EXT ::ext::
#define _EXT_BEGIN namespace ext {
#define _EXT_END } // namespace ext
#define _EXT_DETAIL_BEGIN namespace ext::detail {
#define _EXT_DETAIL_END } // namespace ext::detail

#define _T true
#define _F false

#define catch_all catch (...)
#define catch_specific(exception_t) catch(const exception_t& exception)
#define catch_other catch (...)

#define string_switch(_String) switch(std::hash<size_t>{}(_String))
#define string_case(_String) case(std::hash<size_t>{}(_String))
#define string_default default

#define number_switch(_Number) switch((decltype(_EXT number{_Number})::primitive_t)_Number)
#define number_case(_Number) case((decltype(_EXT number{_Number})::primitive_t)_Number)
#define number_default default

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
#define for_if(if_statement, for_statement) if (if_statement) for (for_statement)


#endif //SBROWSER2_KEYWORDS_HPP

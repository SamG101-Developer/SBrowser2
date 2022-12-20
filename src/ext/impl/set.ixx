module;
#include "ext/macros/namespaces.hpp"
#include <ankerl/unordered_dense.h>


export module ext.core:set;
import :vector;


_EXT_BEGIN
    export template <typename T>
    using set = ankerl::unordered_dense::set<T, ankerl::unordered_dense::hash<T>, std::equal_to<T>, _EXT vector<T>>;
_EXT_END


_EXT_SECURE_BEGIN
    export template <typename T>
    using set = ankerl::unordered_dense::set<T, ankerl::unordered_dense::hash<T>, std::equal_to<T>, _EXT secure::vector<T>>;
_EXT_SECURE_END

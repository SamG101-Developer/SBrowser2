module;
#include "ext/macros/namespaces.hpp"
#include <veque.hpp>


export module ext.vector;
import ext.allocator;


_EXT_BEGIN
    export template <typename T>
    using vector = veque::veque<T, veque::fast_resize_traits, _EXT allocator<T>>;

    export template <typename T>
    using frozen_vector = const vector<T>;
_EXT_END


_EXT_SECURE_BEGIN
    export template <typename T>
    using vector = veque::veque<T, veque::fast_resize_traits, _EXT secure::allocator<T>>;

    export template <typename T>
    using frozen_vector = const vector<T>;
_EXT_SECURE_END

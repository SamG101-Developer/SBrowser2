module;
#include "ext/macros/namespaces.hpp"


export module ext.core:assertion;
//#include <assert.hpp>


_EXT_BEGIN
//    using namespace ::libassert;

    export template <typename ...Args>
    auto assert_(auto&& expression, Args&&... args) {}
//    {ASSERT(expression, std::forward<Args>(args)...);};
_EXT_END

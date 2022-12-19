module;
#include "ext/macros/namespaces.hpp"
#include <assert.hpp>


export module ext.assertion;


_EXT_BEGIN
    using namespace libassert;

    export template <typename ...Args>
    auto assert_(auto&& expression, Args&&... args)
    {ASSERT(expression, std::forward<Args>(args)...);};
_EXT_END

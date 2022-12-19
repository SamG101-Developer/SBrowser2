module;
#include "ext/macros/namespaces.hpp"
#include <assert.hpp>


#undef assert


_EXT_BEGIN
    using namespace libassert;

    template <typename ...Args>
    auto assert(auto&& expression, Args&&... args)
    {ASSERT(expression, std::forward<Args>(args)...);};
_EXT_END


export module ext.assertion;

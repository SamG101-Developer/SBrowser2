#ifndef SBROWSER2_ASSERT_HPP
#define SBROWSER2_ASSERT_HPP

#include "ext/boolean.hpp"
#include <cassert>


_EXT_BEGIN

auto assert_true(bool statement) -> void {assert(statement);}
auto assert_false(bool statement) -> void {assert(!statement);}

_EXT_END


#endif //SBROWSER2_ASSERT_HPP

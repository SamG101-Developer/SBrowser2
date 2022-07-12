#ifndef SBROWSER2_ASSERT_HPP
#define SBROWSER2_ASSERT_HPP

#include "ext/boolean.hpp"
#include <cassert>
namespace ext {auto assert_true (bool statement) -> void;}
namespace ext {auto assert_false(bool statement) -> void;}


auto ext::assert_true(bool statement) -> void
{
    assert(statement);
}


auto ext::assert_false(bool statement) -> void
{
    assert(!statement);
}


#endif //SBROWSER2_ASSERT_HPP

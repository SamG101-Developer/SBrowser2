#ifndef SBROWSER2_SRC_EXT_STACK_HPP
#define SBROWSER2_SRC_EXT_STACK_HPP

#include "ext/view.hpp"
#include <plf_stack.h>


_EXT_BEGIN

using namespace plf;


// an `ext::stack_view<T>` is a view whose iterator is the iterator of an `ext::stack<T>` with template arguments. it
// differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::stack<T>`
// to the 'ext::stack_view<T>`
template <typename _Tx>
struct stack_view : public view<_Tx>
{
    using view<typename stack<_Tx>::iterator>::view;

    explicit stack_view(const stack<_Tx>& other)
            : view<typename stack<_Tx>::iterator>{&other.top(), other.size()}
    {}
};

_EXT_END


#endif //SBROWSER2_SRC_EXT_STACK_HPP

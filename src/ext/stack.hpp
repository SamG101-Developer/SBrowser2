#ifndef SBROWSER2_SRC_EXT_STACK_HPP
#define SBROWSER2_SRC_EXT_STACK_HPP

#include "ext/vector.hpp"
#include "ext/view.hpp"
#include <stack>
#include <plf_stack.h>


_EXT_BEGIN

//using namespace plf;

template <typename T, typename C = vector<T>>
using stack = std::stack<T, C>;


#define stack_view_iterator typename stack<T>::pointer

// an `ext::stack_view<T>` is a view whose iterator is the iterator of an `ext::stack<T>` with template arguments. it
// differs from the base `ext::view<T>` because there is a custom constructor that converts the normal `ext::stack<T>`
// to the 'ext::stack_view<T>`
template <typename T>
struct stack_view : public view<stack_view_iterator>
{
    using view<stack_view_iterator>::view;

    explicit stack_view(stack<T>&& other)
            : view<stack_view_iterator>{&std::move(other.top()), other.size()}
    {}

    explicit stack_view(const stack<T>& other)
            : view<stack_view_iterator>{&other.top(), other.size()}
    {}
};

_EXT_END


#endif //SBROWSER2_SRC_EXT_STACK_HPP

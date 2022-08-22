#ifndef SBROWSER2_FUNCTIONAL_HPP
#define SBROWSER2_FUNCTIONAL_HPP

#include "ext/tuple.hpp"
#include <function2/function2.hpp>


// TODO : test performance against C++ std implementations (bind_front)
// TODO : are arguments being forwarded out of tuple into method?
// TODO : are arguments being forwarded correctly?


_EXT_BEGIN

using namespace fu2;


struct identity
{
    template <typename T>
    constexpr auto operator()(T&& object) const {return std::forward<T>(object);}
};


struct invoke
{
    template <typename T>
    constexpr auto operator()(T&& object) const {return object();}
};


// bind arguments to the back of a method, so that when the partial-method is called with arguments, they will the front
// n arguments (using because std::bind_back isn't available yet on MSVC)
template <typename F, typename ...Args0>
struct bind_back
{
public:
    explicit bind_back(const F& function, Args0&&... fixed_args)
            : m_function{function}
            , m_back_args{ext::make_tuple(std::forward<Args0>(fixed_args)...)}
    {
        // initialize the function and the back arguments, by forwarding the arguments into a tuple and setting this as
        // 'm_back_args' TODO: ext::forward_as_tuple doesn't work here
    }

    template <typename ...Args1>
    constexpr auto operator()(Args1&&... variable_args) const
    {
        // forward the new arguments into a tuple, concatenate this to the beginning of the 'm_front_args', and apply this
        // tuple to the 'm_function', so that the function is invoked with all the arguments
        auto m_front_args = ext::make_tuple(std::forward<Args1>(variable_args)...);
        return ext::apply(m_function, ext::tuple_cat(m_front_args, m_back_args));
    }

private:
    const F& m_function;
    tuple<Args0...> m_back_args;
};


// bind arguments to the front of a method, so that when the partial-method is called with arguments, they will the back
// n arguments (using because std::bind_back isn't available yet on MSVC, so conform with ext::bind_back)
template <typename F, typename ...Args0>
struct bind_front
{
public:
    explicit bind_front(const F& function, Args0&&... fixed_args)
            : m_function{function}
            , m_front_args{ext::make_tuple(std::forward<Args0>(fixed_args)...)}
    {
        // initialize the function and the front arguments, by forwarding the arguments into a tuple and setting this as
        // as 'm_front_args' TODO: ext::forward_as_tuple doesn't work here
    };

    template <typename ...Args1>
    constexpr auto operator()(Args1&&... variable_args) const
    {
        // forward the new arguments into a tuple, concatenate this to the end of the 'm_back_args', and apply this tuple
        // to the 'm_function', so that the function is invoked with all the arguments
        auto m_back_args = ext::make_tuple(std::forward<Args1>(variable_args)...);
        return ext::apply(m_function, ext::tuple_cat(m_front_args, m_back_args));
    }

private:
    const F& m_function;
    tuple<Args0...> m_front_args;
};

_EXT_END


#endif //SBROWSER2_FUNCTIONAL_HPP

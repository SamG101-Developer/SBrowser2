#ifndef SBROWSER2_CONCEPTS_HPP
#define SBROWSER2_CONCEPTS_HPP

#include <range/v3/range/concepts.hpp>


// check if a templated class is a base of another class (don't need template type to check)
template <template <typename> typename _Base, typename _Derived>
concept inherit_template = requires(_Derived _Obj)
{
    []<typename _Ty>(const _Base<_Ty>&){}(_Obj);
};


// check if a class is a base of another class
template <typename _Base, typename _Derived>
concept inherit = requires (_Derived)
{
    std::is_base_of_v<_Base, _Derived>;
};


// check if a type is iterable ie does it have .begin() and .end() iterator access
template <typename _Tx>
concept iterable = requires (_Tx _Obj)
{
    _Obj.begin(); _Obj.end();
};


// check if a type is a smart pointer
template <typename _Tx>
concept smart_pointer = requires (_Tx _Obj)
{
    _Obj.get() == &*_Obj;
};


// check if a pointer can be dynamically cast to another pointer TODO : _`Tx* ...` and `<_Tx1*>` ?
template <typename _Tx, typename _Tx1>
concept dynamically_castable_to = requires (_Tx _PtrL)
{
    dynamic_cast<_Tx1>(_PtrL);
};


// check if a type is a range_v3 type
template <typename _Tx>
concept range_v3_view = requires(_Tx&& range)
{
    ranges::view_<_Tx>;
};


// check if 1 type matches any types
template <typename ..._TypesToCheckAgainst, typename ..._TypesToCheck>
concept same_as_any = requires(_TypesToCheck...)
{
    ((std::same_as<_TypesToCheck, _TypesToCheckAgainst> || ...) && ...);
};


// check if all types match 1 type
template <typename _Tx, typename ..._Valty>
concept all_same_as = requires(_Valty...)
{
    (std::same_as<_Valty, _Tx> && ...);
};


// check if any types match 1 type
template <typename _Tx, typename ..._Valty>
concept any_same_as = requires(_Valty...)
{
    (std::same_as<_Valty, _Tx> || ...);
};


// check if a type is a primitive numeric type
template <typename _Tx>
concept primitive_numeric = requires(_Tx)
{
    std::integral<_Tx> || std::floating_point<_Tx>;
};


// check if a type is callable
template <typename _Tx>
concept callable = requires(_Tx)
{
    std::invocable<_Tx>;
};


#endif //SBROWSER2_CONCEPTS_HPP

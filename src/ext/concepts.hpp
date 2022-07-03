#ifndef SBROWSER2_CONCEPTS_HPP
#define SBROWSER2_CONCEPTS_HPP

#include <range/v3/range/concepts.hpp>


// check if a templated class is a base of another class (don't need template type to check)
template <template <typename> typename _BaseMixin, typename _Derived>
concept inherit_template = requires(_Derived _Obj)
{
    []<typename _Ty>(const _BaseMixin<_Ty>&){}(_Obj);
};


// check if a class is a base of another class
template <typename _Base, typename _Derived>
concept inherit = std::is_base_of_v<_Base, _Derived>;


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
concept range_v3_view = ranges::view_<_Tx>;


// check if a type(s) is another type, works for parameter packs too - are all arguments an integer
template <typename TypeToCheck, typename TypeToCheckAgainst>
concept type_is = std::same_as<std::remove_cvref_t<TypeToCheck>, TypeToCheckAgainst>;


// check if a type(s) is in a list of types, works for parameter pack too - are all arguments a string or node?
template <typename TypeToCheck, typename ...TypesToCheckAgainst>
concept type_in = (std::same_as<std::remove_cvref_t<TypeToCheck>, TypesToCheckAgainst> || ...);


// check if a type is a primitive numeric type
template <typename _Tx>
concept primitive_numeric = std::integral<_Tx> || std::floating_point<_Tx>;


// check if a type is callable
template <typename _Tx>
concept callable = std::invocable<_Tx>;


#endif //SBROWSER2_CONCEPTS_HPP

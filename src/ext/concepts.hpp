#pragma once
#ifndef SBROWSER2_CONCEPTS_HPP
#define SBROWSER2_CONCEPTS_HPP

#include "ext/keywords.hpp"
#include <range/v3/range/concepts.hpp>
#include <type_traits>


_EXT_BEGIN

// check if a templated class is a base of another class (don't need template type to check)
template <template <typename> typename BaseMixin, typename Derived>
concept inherit_template = requires(Derived object)
{
    []<typename T>(const BaseMixin<T>&){}(object); // TODO : forward?
};


// check if a class is a base of another class
template <typename Derived, typename Base>
concept inherit = std::is_base_of_v<Base, Derived>;


// check if a type is iterable ie does it have .begin() and .end() iterator access
template <typename T>
concept iterable = requires (T object)
{
    object.begin(); object.end();
};


// check if a type is a smart pointer
template <typename T>
concept smart_pointer = requires (T object)
{
    object.get() == &*object;
};


// check if a pointer can be dynamically cast to another pointer
template <typename From, typename To>
concept dynamically_castable_to = requires (From pointer)
{
    dynamic_cast<To>(pointer);
};


template <typename T>
concept is_pointer = std::is_pointer_v<T>;

template <typename T>
concept is_reference = std::is_reference_v<T>;

template <typename T>
concept is_rvalue_reference = std::is_rvalue_reference_v<T>;

template <typename T>
concept is_lvalue_reference = std::is_lvalue_reference_v<T>;

template <typename T>
concept is_pointer_or_reference = is_pointer<T> || is_reference<T>;

template <typename T>
concept is_const = std::is_const_v<T> || (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>);



// check if a type is a range_v3 type
template <typename T>
concept range_v3_view = ranges::view_<T>;


// check if a type(s) is in a list of types, works for parameter pack too; checks if all arguments are of a certain
// type or types for example `auto function(type_is<ext::string, ext::number<int>> auto&&... args) -> void`?
template <typename TypeToCheck, typename ...TypesToCheckAgainst>
concept type_is = (std::same_as<std::remove_cvref_t<TypeToCheck>, TypesToCheckAgainst> || ...);

template <typename TypeToCheck, template <typename> typename ...TemplatedTypesToCheckAgainst>
concept type_is_any_specialization = (inherit_template<TemplatedTypesToCheckAgainst, TypeToCheck> || ...);

template <typename TypeTpCheck, typename ...TypesToCheckAgainst>
concept type_is_not = (!std::same_as<std::remove_cvref<TypeTpCheck>, TypesToCheckAgainst> && ...);


// check if a type is a primitive numeric type
template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;


// check if a type is callable
template <typename T>
concept callable = requires
{
    requires requires{std::invocable<T>;}                        // Handles general invocable objects
            || requires {T::operator();}                         // Handles functors
            || requires {std::is_function_v<T>;}                 // Handles functions
            || requires {std::is_member_function_pointer_v<T>;}; // Handles function pointers (class members)
};


// check if a type is iterator-like
template <typename T>
concept iterator_like = std::is_pointer_v<std::remove_pointer_t<T>>;


// check if a type is an enum type
template <typename T>
concept type_is_enum = std::is_enum_v<T> || std::is_scoped_enum_v<T>;

_EXT_END;


#endif //SBROWSER2_CONCEPTS_HPP

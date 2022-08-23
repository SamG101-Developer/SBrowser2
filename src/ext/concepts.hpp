#ifndef SBROWSER2_CONCEPTS_HPP
#define SBROWSER2_CONCEPTS_HPP

#include "ext/keywords.hpp"
#include <range/v3/range/concepts.hpp>
#include <type_traits>


// check if a templated class is a base of another class (don't need template type to check)
template <template <typename> typename BaseMixin, typename Derived>
concept inherit_template = requires(Derived object)
{
    []<typename T>(const BaseMixin<T>&){}(object); // TODO : forward?
};


// check if a class is a base of another class
template <typename Derived, typename Base>
concept inherit = requires
{
    requires std::is_base_of_v<Base, Derived>;
};


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
concept callable = requires (T&& object)
{
    std::invocable<T> || object.operator();
};


// check if a type is iterator-like
template <typename T>
concept iterator_like = std::is_pointer_v<std::remove_pointer_t<T>>;


// check if a type is an enum type
template <typename T>
concept type_is_enum = std::is_enum_v<T> || std::is_scoped_enum_v<T>;


#endif //SBROWSER2_CONCEPTS_HPP

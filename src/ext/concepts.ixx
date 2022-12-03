module;
#include "ext/macros/namespaces.hpp"
#include <range/v3/range/concepts.hpp>

export module ext.concepts;
import std.core;


_EXT_BEGIN
    // check if a templated class is a base of another class (don't need template type to check)
    export template <template <typename> typename BaseMixin, typename Derived>
    concept inherit_template = requires(Derived object)
    {[]<typename T>(const BaseMixin<T>&){}(object);};


    // check if a class is a base of another class
    export template <typename Derived, typename Base>
    concept inherit = std::is_base_of_v<Base, Derived>;


    // check if a type is iterable ie does it have .begin() and .end() iterator access
    export template <typename T>
    concept iterable = requires (T object)
    {object.begin(); object.end();};


    // check if a type is a smart pointer
    export template <typename T>
    concept smart_pointer = requires (T object)
    {object.get() == &*object;};


    // check if a pointer can be dynamically cast to another pointer
    export template <typename From, typename To>
    concept dynamically_castable_to = requires (From pointer)
    {dynamic_cast<To>(pointer);};


    export template <typename T>
    concept is_pointer = std::is_pointer_v<T>;

    export template <typename T>
    concept is_reference = std::is_reference_v<T>;

    export template <typename T>
    concept is_rvalue_reference = std::is_rvalue_reference_v<T>;

    export template <typename T>
    concept is_lvalue_reference = std::is_lvalue_reference_v<T>;

    export template <typename T>
    concept is_pointer_or_reference = is_pointer<T> || is_reference<T>;

    export template <typename T>
    concept is_const = std::is_const_v<T> || (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>);

    // check if a type is a range_v3 type
    export template <typename T>
    concept range_v3_view = ranges::view_<T>;

    // check if a type(s) is in a list of types, works for parameter pack too; checks if all arguments are of a certain
    // type or types for example `auto function(type_is<ext::string, ext::number<int>> auto&&... args) -> void`?
    export template <typename TypeToCheck, typename ...TypesToCheckAgainst>
    concept type_is = (std::same_as<std::remove_cvref_t<TypeToCheck>, TypesToCheckAgainst> || ...);

    export template <typename TypeToCheck, template <typename> typename ...TemplatedTypesToCheckAgainst>
    concept type_is_any_specialization = (_EXT inherit_template<TemplatedTypesToCheckAgainst, TypeToCheck> || ...);

    export template <typename TypeTpCheck, typename ...TypesToCheckAgainst>
    concept type_is_not = (!std::same_as<std::remove_cvref<TypeTpCheck>, TypesToCheckAgainst> && ...);


    // check if a type is a primitive numeric type
    export template <typename T>
    concept arithmetic = std::integral<T> || std::floating_point<T>; // || _EXT type_is<T, bigint>;


    // check if a type is callable
    export template <typename T>
    concept callable = requires
    {
        requires requires {T::operator();}                           // Handles functors
                || requires {std::is_function_v<T>;}                 // Handles functions
                || requires {std::is_member_function_pointer_v<T>;}; // Handles function pointers (class members)
    };


    // check if a type is iterator-like
    export template <typename T>
    concept iterator_like = std::is_pointer_v<std::remove_pointer_t<T>>;

    // check if a type is an enum type
    export template <typename T>
    concept type_is_enum = std::is_enum_v<T> || std::is_scoped_enum_v<T>;

    export template <typename T>
    concept is_unique = _EXT type_is_any_specialization<T, std::unique_ptr>;
_EXT_END

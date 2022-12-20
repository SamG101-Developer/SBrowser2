module;
#include "ext/macros/namespaces.hpp"
#include <concepts>
#include <range/v3/range/concepts.hpp>


export module ext.core:concepts;


_EXT_BEGIN
    // Check if a class inherits any specialization of a mixin-type (templated) by making the concept call a lambda with
    // a templated parameter of the mixin-type; if the mixin is inherited then there won't by a static error.
    export template <template <typename> typename BaseMixin, typename Derived>
    concept inherit_template = requires(Derived object)
    {[]<typename ...Ts>(BaseMixin<Ts...>*){}(object);};

    // Check if a class inherits another class-type, by using the built-in std concept that checks if a class-type
    // derives from another class type.
    export template <typename Derived, typename Base>
    concept inherit =
            std::derived_from<Derived, Base>;

    // Check if a type is an iterable -- to be an iterable it must have begin() and end() iterator methods. The return
    // type isn't fixed or bound to a container type because ranges use sentinels, which arent means that the begin()
    // and end() iterators have different types.
    export template <typename T>
    concept iterable = requires (T object)
    {object.begin(); object.end();};

    // Check if an iterable is a range-v3 view -- if the begin() and end() methods are different types then the end()
    // type is a sentinel. TODO : switch decltype(declval<...>(...)) to std::result_of_t<...>?
    export template <typename T>
    concept range_iterable =
            iterable<T> && !std::is_same_v<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>;

    export template <typename T>
    concept pure_iterable =
            iterable<T> && std::is_same_v<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>;

    // Check if a type is a smart pointer -- to be a smart pointer it's get() method that access the underlying object
    // much return the same pointer as the address of the dereference operator (which returns the reference to the
    // object underlying the smart pointer).
    export template <typename T>
    concept smart_pointer = requires (T object)
    {object.get() == &*object;};

    // Check if a type is a pointer -- wrap the std struct that does the same thing.
    export template <typename T>
    concept is_pointer =
            std::is_pointer_v<T>;

    // Check if a type is a reference -- wrap the std struct that does the same thing.
    export template <typename T>
    concept is_reference =
            std::is_reference_v<T>;

    // Check if a type is a rvalue-reference -- wrap the std struct that does the same thing.
    export template <typename T>
    concept is_rvalue_reference =
            std::is_rvalue_reference_v<T>;

    // Check if a type is a lvalue-reference -- wrap the std struct that does the same thing.
    export template <typename T>
    concept is_lvalue_reference =
            std::is_lvalue_reference_v<T>;

    // Check if a type is a pointer or reference -- check that either the type is a pointer or reference using the
    // already defined concepts.
    export template <typename T>
    concept is_pointer_or_reference =
            is_pointer<T> || is_reference<T>;

    // Check if a type is const -- an object is const if it carries the const object or is a pointer to a const object,
    // which is determined by checking the const-ness of the type whose pointer has been removed. TODO : does this work?
    export template <typename T>
    concept is_const =
            std::is_const_v<T> || (std::is_pointer_v<T> && std::is_const_v<std::remove_pointer_t<T>>);

    // Check if a pointer can be dynamically cast to another pointer -- this is just done by making the concept call a
    // dynamic cast on the types From -> To. TODO : constrain _EXT is_pointer_or_reference
    export template <typename From, typename To>
    concept dynamically_castable_to = requires (From pointer)
    {dynamic_cast<To>(pointer);};


    // Check if a type is a range_v3 type -- wrap the ranges-v3 concept that does the same thing.
    export template <typename T>
    concept range_v3_view =
            ranges::view_<T>;

    // Check if a type(s) is in a list of types, works for parameter pack too; checks if all arguments are of a certain
    // type or types for example `auto function(type_is<ext::string, ext::number<int>> auto&&... args) -> void`?
    export template <typename TypeToCheck, typename ...TypesToCheckAgainst>
    concept type_is =
            (std::same_as<std::remove_cvref_t<TypeToCheck>, TypesToCheckAgainst> || ...);

    export template <typename TypeToCheck, template <typename> typename ...TemplatedTypesToCheckAgainst>
    concept type_is_any_specialization =
            (_EXT inherit_template<TemplatedTypesToCheckAgainst, TypeToCheck> || ...);

    export template <typename TypeTpCheck, typename ...TypesToCheckAgainst>
    concept type_is_not =
            (!std::same_as<std::remove_cvref<TypeTpCheck>, TypesToCheckAgainst> && ...);


    // check if a type is a primitive numeric type
    export template <typename T>
    concept arithmetic =
            std::integral<T> || std::floating_point<T>; // || _EXT type_is<T, bigint>;


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
    concept iterator_like =
            std::is_pointer_v<std::remove_pointer_t<T>>;

    // check if a type is an enum type
    export template <typename T>
    concept type_is_enum =
            std::is_enum_v<T> || std::is_scoped_enum_v<T>;

    export template <typename T>
    concept is_unique =
            _EXT type_is_any_specialization<T, std::unique_ptr>;

    export template <typename T>
    concept has_pimpl = requires
    {{T::d_func()};};
_EXT_END

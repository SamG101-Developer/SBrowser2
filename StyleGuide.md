# STech Style Guide

## Class definition (.hpp)
```C++
class class_name
        : public base_class_a
        , public base_class_b
        , public templated_class_a<template_parameter_1>
        , public templated_class_b<template_parameter_1>
{
    public constructors:
    public js_methods:
    private js_properties:
    
    protected cpp_methods:
    protected cpp_properties:
    
    private cpp_methods:
    private cpp_properties:
};
```

## Namespace definition methods (.hpp)
```C++
namespace namespace_name
{
    auto method_name_a(
            parameter_type_1 argument_1,
            parameter_type_2 argument_2)
            -> return_type_1;
    
    auto method_name_b()
            -> return_type_1;
}
```


## Class definition methods (.hpp)
```C++
class class_name
{
    auto method_name_a(parameter_type_1 argument_1, parameter_type_2 argument_2) const -> return_type_1;
    auto method_name_b(parameter_type_1 argument_1, parameter_type_2 argument_2) const -> return_type_2;
};
```

## Class declaration method (.hpp)
```C++
inline auto class_name::method_name_a(parameter_type_1 argument_1, parameter_type_2 argument_2) -> return_type_1
{
    ...
}

inline auto class_name::method_name_b(
        very_long_parameter_type_1 very_long_argument_1, very_long_parameter_type_2 very_long_argument_2) -> very_long_return_type
```

## Class declaration method (.cpp)
```C++
auto class_name::short_method_signature(parm_t_1, arg_1) -> ret_t
{
    ...
}

auto class_name::long_method_signature(
        parameter_type_1 argument_1,
        parameter_type_2 argument_2)
        const && -> return_type_1
{
    ...
}
```

## Primitives vs Objects
 - Use primitives for template types - `template <int size>`
 - Use object versions (`ext::boolean`, `ext::number<_Tx>`) everywhere else


## Concepts
 - Always use inline parameter types if possible (constrain parameter)
   - `auto function(concept_name auto parameter_a) -> return_type_a;`.
 - Use trailing requires on the method when: function constrained based on class template
   - `template <typename _Tx> struct struct_name_a {auto method_a(_Tx a) -> int requires concept_name<_Tx> {}}`.
 - Use template constraint when: class template is constrained
   - `template <concept_name _Tx> ...`
 - Never need to use trailing requires on the template -> use template constraint
   - `template <typename _Tx> requires (concept_name<_Tx>)`.

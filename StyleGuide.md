# STech Style Guide

## Class definition (.hpp)
```c++
class class_name
        : public base_class_a
        , public base_class_b
        , public templated_class_a<template_parameter_1>
        , public templated_class_b<template_parameter_1>
{
public constructors:
public js_methods:
public js_properties:
    
protected cpp_methods:
protected cpp_properties:
    
private cpp_methods:
private cpp_properties:
};
```

## Class definition constructors (.hpp)
### Rule of 5
```c++
template <typename template_parameter_1>
class class_name
{
    class_name();
    class_name(const class_name&);
    class_name(class_name&&) noexcept;
    auto operator=(const class_name&) -> class_name&;
    auto operator=(class_name&&) noexcept -> class_name&;
};
```

### Rule of 5 + 1
```c++
template <typename template_parameter_1>
class class_name
{
    class_name();
    ~class_name();
    
    class_name(const class_name&);
    class_name(class_name&&) noexcept;
    auto operator=(const class_name&) -> class_name&;
    auto operator=(class_name&&) noexcept -> class_name&;
};
```

### Rule of 5 + 1 + 4 (+1)
```c++
template <typename template_parameter_1>
class class_name
{
    class_name();
    ~class_name();
    
    class_name(const class_name&);
    class_name(class_name&&) noexcept;
    auto operator=(const class_name&) -> class_name&;
    auto operator=(class_name&&) noexcept -> class_name&;
    
    class_name(const template_parameter_1&);
    class_name(template_parameter_1&&) noexcept;
    auto operator=(const template_parameter_1&) -> class_name&;
    auto operator=(template_parameter_1&&) noexcept -> class_name&;
    
    template <typename ..._Valty> class_name(_Valty... _Val); // Optional
};
```

## Class definition methods (.hpp)
```c++
class class_name
{
    auto method_name_a(parameter_type_1 argument_1, parameter_type_2 argument_2) const -> return_type_1;
    auto method_name_b(parameter_type_1 argument_1, parameter_type_2 argument_2) const -> return_type_2;
};
```

## Class declaration method (.hpp)
```c++
inline auto class_name::method_name_a(parameter_type_1 argument_1, parameter_type_2 argument_2) -> return_type_1
{
    ...
}
```

## Class declaration method (.cpp)
```c++
auto class_name::method_name_a(
        parameter_type_1 argument_1,
        parameter_type_2 argument_2)
        const
        -> return_type_1
{
    ...
}
```

## Primitives vs Objects
 - Use primitives for template types or temporary objects - `template <int size>`, `ext::boolean check = true`
 - Use object versions (ext::boolean, ext::number<T>) everywhere else
 - Pass ext::boolean, ext::number<T> by value to act like primitives


export module ext.any;

import ext.macros.annotations;
import ext.macros.namespaces;
import ext.boolean;
import ext.concepts;
import ext.number;
import std.core;


_EXT_BEGIN

export class any;

template <typename T>
concept not_any = !_EXT type_is<T, any>;


export class any final
{
public friends:
     friend struct std::hash<ext::any>;

public constructors:
    any() = default;
    ~any() = default;

    any(const any&) = default;
    any(any&&) noexcept = default;
    auto operator=(const any&) -> any& = default;
    auto operator=(any&&) noexcept -> any& = default;

    template <not_any T> any(T&& value) noexcept;
    template <not_any T> auto operator=(const T& value) -> any&;
    template <not_any T> auto operator=(T&& value) noexcept -> any&;

    auto operator==(const any& other) const -> bool;
    template <not_any T> auto operator==(T&& other) const -> bool;

public:
    [[nodiscard]] auto type() const -> const type_info&;
    [[nodiscard]] auto is_arithmetic_type() const -> boolean;
    [[nodiscard]] auto is_empty() const -> boolean;
    [[nodiscard]] auto has_value() const -> boolean;
    template <typename T> auto to() const -> T;
    template <is_rvalue_reference T> auto to() const -> T;
    template <typename T> auto try_to() const -> _EXT boolean;

private:
    std::any m_any;
    _EXT boolean m_is_arithmetic;
    _EXT number<size_t> m_hash = 0;
};

_EXT_END


template <_EXT not_any T>
ext::any::any(T&& value) noexcept
        : m_any{std::forward<T>(value)}
        , m_is_arithmetic{type_is_any_specialization<T, number>}
        // TODO: , m_hash{std::hash<T>{}(std::forward<T>(value))}
{}


template <_EXT not_any T>
auto ext::any::operator=(const T& value) -> any&
{
    m_any = value;
    m_is_arithmetic = type_is_any_specialization<T, number>;
    m_hash = std::hash<T>{}(std::forward<T>(value));
    return *this;
}


template <_EXT not_any T>
auto ext::any::operator=(T&& value) noexcept -> any&
{
    m_any = std::forward<decltype(value)>(value);
    m_is_arithmetic = type_is_any_specialization<T, number>;
    m_hash = std::hash<T>{}(std::forward<T>(value));
    return *this;
}


auto ext::any::type() const -> const type_info&
{return m_any.type();}


auto ext::any::is_arithmetic_type() const -> boolean
{return m_is_arithmetic;}


auto ext::any::is_empty() const -> boolean
{return !m_any.has_value();}


auto ext::any::has_value() const -> boolean
{return m_any.has_value();}


template <typename T>
auto ext::any::to() const -> T
{return std::any_cast<T>(m_any);}


template <is_rvalue_reference T>
auto ext::any::to() const -> T
{return std::move(std::any_cast<T&&>(m_any));}


template <typename T>
auto ext::any::try_to() const -> ext::boolean
{return noexcept(to<T>());}


auto ext::any::operator==(const ext::any& other) const -> bool
{return m_hash == other.m_hash;}


template <_EXT not_any T>
auto ext::any::operator==(T&& other) const -> bool
{return std::forward<T>(other) == to<T>();}

#pragma once
#ifndef SBROWSER2_STRING_HPP
#define SBROWSER2_STRING_HPP

#include <string>
#include <string_view>

namespace ext {class string;}
namespace ext {class string_view;}

#include <QtCore/QString>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-primitive.h>
#include <ext/keywords.hpp>


class ext::string
        : inherits public std::string
{
public constructors:
    string() = default;
    ~string() {clear();}

    string(const string&) = default;
    string(string&&) noexcept = default;
    auto operator=(const string&) -> string& = default;
    auto operator=(string&&) noexcept -> string& = default;

    explicit string(const char* _Other) : std::string(_Other) {};
    auto operator=(const char* _Other) -> string& {std::string::operator=(_Other);};

public cpp_operators:
    [[nodiscard]] auto to_qt_string() const -> QString {return {c_str()};}
    [[nodiscard]] auto to_v8_string() const -> v8::Local<v8::String> {return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), c_str()).ToLocalChecked();}

    [[nodiscard]] static auto from_qt_string(const QString& _That) -> ext::string {return string{_That.toStdString().c_str()};}
    [[nodiscard]] static auto from_v8_string(const v8::Local<v8::String> _That) -> ext::string {return string{*v8::String::Utf8Value{v8::Isolate::GetCurrent(), _That}};}
};


class ext::string_view
        : inherits public std::string_view
{
public constructors:
    string_view() = default;

    string_view(const string_view&) = default;
    string_view(string_view&&) noexcept = default;
    auto operator=(const string_view&) const -> string_view& = delete;
    auto operator=(string_view&&) const noexcept -> string_view& = delete;

    explicit string_view(const string& _Other) : std::string_view{_Other} {};
    explicit string_view(string&& _Other) noexcept : std::string_view{std::forward<string>(_Other)} {};
    auto operator=(const string&) const -> string_view& = delete;
    auto operator=(string&&) const noexcept -> string_view& = delete;

    explicit string_view(const char* _Other) : std::string_view{_Other} {};
};

#endif //SBROWSER2_STRING_HPP

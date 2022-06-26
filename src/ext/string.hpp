#pragma once
#ifndef SBROWSER2_STRING_HPP
#define SBROWSER2_STRING_HPP

#include <string>
#include <string_view>
namespace ext {class string;}
namespace ext {class string_view;}
using sv = ext::string_view;

#include <ext/keywords.hpp>
#include <v8-isolate.h>
#include <v8-local-handle.h>
#include <v8-primitive.h>
#include <QtCore/QString>


class ext::string_view
        : public std::string_view
{
public constructors:
    using std::string_view::string_view;
    using std::string_view::iterator;
    string_view(const char* _Other) : std::string_view{_Other} {}

public cpp_methods: // TODO -> is .data() safe?
    operator QString() const {return {data()};}
    operator v8::Local<v8::String>() const {return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), data()).ToLocalChecked();}
    operator bool() {return !empty();}
    operator ext::string();

    constexpr explicit operator const char*() {return data();}

    auto operator !() -> ext::boolean {return empty();}
};


class ext::string
        : public std::string
{
public constructors:
    using std::string::string;

    auto operator=(const char*) -> string&;

public cpp_methods:
    [[nodiscard]] static auto from_qt_string(const QString& _That) -> ext::string {return string{_That.toStdString().c_str()};}
    [[nodiscard]] static auto from_v8_string(v8::Local<v8::String> _That) -> ext::string {return string{*v8::String::Utf8Value{v8::Isolate::GetCurrent(), _That}};}

public cpp_operators:
    operator QString() const {return {c_str()};}
    operator v8::Local<v8::String>() const {return v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), c_str()).ToLocalChecked();}
    operator bool() {return !empty();}
    operator string_view() {return string_view{c_str()};};

    auto operator !() -> ext::boolean {return empty();}
};


#endif //SBROWSER2_STRING_HPP

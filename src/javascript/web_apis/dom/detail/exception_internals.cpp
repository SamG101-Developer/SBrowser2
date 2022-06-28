#include "exception_internals.hpp"

#include <range/v3/algorithm/fold_left.hpp>
#include <v8-exception.h>


struct exception_string_formatter
{
    constexpr auto operator()(const ext::string& left, const ext::string& right) const -> ext::string
    {
        return left + "\t-" + right + "\n";
    }

    template <typename V>
    constexpr auto operator()(const ext::string& left, std::pair<ext::string, V>&& right) const -> ext::string
    {
        return left + right.first + ": " + std::to_string(right.second) + "\n";
    }
};


template <v8_primitive_error_t exception_type>
auto dom::detail::exception_internals::throw_v8_exception(
        exception_condiditional_t&& condition, ext::string_view exception_message) -> void
{
    if (std::move(condition)())
    {
        // create the v8 primitive exception object, and set its type based on the enum value
        v8::Local<v8::Value> v8_primitive_exception_object;
        switch(exception_type)
        {
            case V8_TYPE_ERROR: v8_primitive_exception_object = v8::Exception::TypeError(exception_message);
            case V8_RANGE_ERROR: v8_primitive_exception_object = v8::Exception::RangeError(exception_message);
            case V8_REFERENCE_ERROR: v8_primitive_exception_object = v8::Exception::ReferenceError(exception_message);
            case V8_SYNTAX_ERROR: v8_primitive_exception_object = v8::Exception::SyntaxError(exception_message);
            case V8_WASM_COMPILE_ERROR: v8_primitive_exception_object = v8::Exception::WasmCompileError(exception_message);
            case V8_WASM_LINK_ERROR: v8_primitive_exception_object = v8::Exception::WasmLinkError(exception_message);
            case V8_WASM_RUNTIME_ERROR: v8_primitive_exception_object = v8::Exception::WasmRuntimeError(exception_message);
            default: v8_primitive_exception_object = v8::Exception::Error(exception_message);
        }

        // the condition has already been asserted, so throw the exception
        v8::Isolate::GetCurrent()->ThrowException(v8_primitive_exception_object);
    }
}


template <v8_custom_error_t exception_type>
auto dom::detail::exception_internals::throw_v8_exception_formatted(
        exception_condiditional_t&& condition,
        ext::string_view description,
        ext::string_vector&& possible_causes,
        ext::string_vector&& possible_fixes,
        auto&& ...object_information)
        -> void
{
    if (std::move(condition)())
    {
        // start the error message with the description
        ext::string exception_message = description;

        // bullet point the possible causes (if there are any)
        if (!possible_causes.empty())
        {
            exception_message += "\n\nPossible causes:\n";
            ranges::fold_left(std::move(possible_causes), exception_message, exception_string_formatter{});
        }

        // bullet point the possible fixes (if there are any)
        if (!possible_fixes.empty())
        {
            exception_message += "\n\nPossible fixes:\n";
            ranges::fold_left(std::move(possible_fixes), exception_message, exception_string_formatter{});
        }

        // bullet point the relevant information / memory addresses of objects
        exception_message += "\n\nRelevant information / memory addresses:\n";
        ranges::fold_left(std::forward<decltype(object_information)>(object_information)..., exception_message, exception_string_formatter{});

        // the 'condition' has already been asserted, so throw the exception
        v8::Isolate::GetCurrent()->ThrowError(exception_message);
    }
}

#ifndef SBROWSER2_EXCEPTION_INTERNALS_HPP
#define SBROWSER2_EXCEPTION_INTERNALS_HPP

#include <functional>
#include <tuple>
#include <ext/string.hpp>

#include <range/v3/algorithm/for_each.hpp>

#define NO_CONDITION [](){return true;}
#define P(key, val) std::make_pair(key, val)


enum v8_custom_error_t
{
    INDEX_SIZE_ERR, DOMSTRING_SIZE_ERR, HIERARCHY_REQUEST_ERR, WRONG_DOCUMENT_ERR, INVALID_CHARACTER_ERR,
    NO_DATA_ALLOWED_ERR, NO_MODIFICATION_ALLOWED_ERR, NOT_FOUND_ERR, NOT_SUPPORTED_ERR, INUSE_ATTRIBUTE_ERR,
    INVALID_STATE_ERR, SYNTAX_ERR, INVALID_MODIFICATION_ERR, NAMESPACE_ERR, INVALID_ACCESS_ERR, VALIDATION_ERR,
    TYPE_MISMATCH_ERR, SECURITY_ERR, NETWORK_ERR, ABORT_ERR, URL_MISMATCH_ERR, QUOTA_EXCEEDED_ERR, TIMEOUT_ERR,
    INVALID_NODE_TYPE_ERR, DATA_CLONE_ERR, ENCODING_ERR, NOT_READABLE_ERR, UNKNOWN_ERR, CONSTRAINT_ERR, DATA_ERR,
    TRANSACTION_INACTIVE_ERR, READONLY_ERR, VERSION_ERR, OPERATION_ERR, NOT_ALLOWED_ERR
};


enum v8_primitive_error_t
{
    V8_TYPE_ERROR, V8_RANGE_ERROR, V8_REFERENCE_ERROR, V8_SYNTAX_ERROR, V8_WASM_COMPILE_ERROR, V8_WASM_LINK_ERROR,
    V8_WASM_RUNTIME_ERROR
};


namespace dom::detail::exception_internals
{
    using exception_condiditional_t = std::function<bool()>;

    template <v8_primitive_error_t exception_type>
    auto throw_v8_exception(
            exception_condiditional_t&& condition = NO_CONDITION,
            ext::string_view exception_message = "")
            -> void;

    template <v8_custom_error_t exception_type>
    auto throw_v8_exception_formatted(
            exception_condiditional_t&& condition = NO_CONDITION,
            ext::string_view description = "",
            ext::vector<ext::string>&& possible_causes = {},
            ext::vector<ext::string>&& possible_fixes = {},
            auto&&... object_information)
            -> void;
}


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
        exception_condiditional_t&& condition, ext::string_view description, ext::vector<ext::string>&& possible_causes,
        ext::vector<ext::string>&& possible_fixes, auto&& ...object_information) -> void
{
    if (std::move(condition)())
    {
        // start the error message with the description
        ext::string exception_message = description;

        // bullet point the possible causes (if there are any)
        if (!possible_causes.empty())
        {
            exception_message += "\n\nPossible causes:\n";
            ranges::for_each(std::move(possible_causes), [&exception_message](ext::string&& cause) {exception_message += "\t-" + cause + "\n";});
        }

        // bullet point the possible fixes (if there are any)
        if (!possible_fixes.empty())
        {
            exception_message += "\n\nPossible fixes:\n";
            ranges::for_each(std::move(possible_fixes), [&exception_message](ext::string&& fix) {exception_message += "\t-" + fix + "\n";});
        }

        // bullet point the relevant information / memory addresses of objects
        exception_message += "\n\nRelevant information / memory addresses:\n";
        ranges::for_each(object_information..., [&exception_message]<typename K, typename V>(std::pair<K, V>&& info) {exception_message += std::move(info).first + ": " + std::move(info).second;});

        // the 'condition' has already been asserted, so throw the exception
        v8::Isolate::GetCurrent()->ThrowError(exception_message);
    }
}


#endif //SBROWSER2_EXCEPTION_INTERNALS_HPP

#include "dom_exception.hpp"

#include "dom/detail/exception_internals.hpp"


dom::other::dom_exception::dom_exception(
        ext::string&& message,
        v8_custom_error_t type)

        : message(std::move(message))
        , type(type)
{
}


auto dom::other::dom_exception::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<dom_exception>{isolate}
            .ctor<ext::string_view, v8_custom_error_t>()
            .var("message", &dom::other::dom_exception::message, true)
            .var("type", &dom::other::dom_exception::type, true)
            .static_("INDEX_SIZE_ERR", v8_custom_error_t::INDEX_SIZE_ERR, true)
            .static_("DOMSTRING_SIZE_ERR", v8_custom_error_t::DOMSTRING_SIZE_ERR, true)
            .static_("HIERARCHY_REQUEST_ERR", v8_custom_error_t::HIERARCHY_REQUEST_ERR, true)
            .static_("WRONG_DOCUMENT_ERR", v8_custom_error_t::WRONG_DOCUMENT_ERR, true)
            .static_("INVALID_CHARACTER_ERR", v8_custom_error_t::INVALID_CHARACTER_ERR, true)
            .static_("NO_DATA_ALLOWED_ERR", v8_custom_error_t::NO_DATA_ALLOWED_ERR, true)
            .static_("NO_MODIFICATION_ALLOWED_ERR", v8_custom_error_t::NO_MODIFICATION_ALLOWED_ERR, true)
            .static_("NOT_FOUND_ERR", v8_custom_error_t::NOT_FOUND_ERR, true)
            .static_("NOT_SUPPORTED_ERR", v8_custom_error_t::NOT_SUPPORTED_ERR, true)
            .static_("INUSE_ATTRIBUTE_ERR", v8_custom_error_t::INUSE_ATTRIBUTE_ERR, true)
            .static_("INVALID_STATE_ERR", v8_custom_error_t::INVALID_STATE_ERR, true)
            .static_("SYNTAX_ERR", v8_custom_error_t::SYNTAX_ERR, true)
            .static_("INVALID_MODIFICATION_ERR", v8_custom_error_t::INVALID_MODIFICATION_ERR, true)
            .static_("NAMESPACE_ERR", v8_custom_error_t::NAMESPACE_ERR, true)
            .static_("INVALID_ACCESS_ERR", v8_custom_error_t::INVALID_ACCESS_ERR, true)
            .static_("VALIDATION_ERR", v8_custom_error_t::VALIDATION_ERR, true)
            .static_("TYPE_MISMATCH_ERR", v8_custom_error_t::TYPE_MISMATCH_ERR, true)
            .static_("SECURITY_ERR", v8_custom_error_t::SECURITY_ERR, true)
            .static_("NETWORK_ERR", v8_custom_error_t::NETWORK_ERR, true)
            .static_("ABORT_ERR", v8_custom_error_t::ABORT_ERR, true)
            .static_("URL_MISMATCH_ERR", v8_custom_error_t::URL_MISMATCH_ERR, true)
            .static_("QUOTA_EXCEEDED_ERR", v8_custom_error_t::QUOTA_EXCEEDED_ERR, true)
            .static_("TIMEOUT_ERR", v8_custom_error_t::TIMEOUT_ERR, true)
            .static_("INVALID_NODE_TYPE_ERR", v8_custom_error_t::INVALID_NODE_TYPE_ERR, true)
            .static_("DATA_CLONE_ERR", v8_custom_error_t::DATA_CLONE_ERR, true)
            .static_("ENCODING_ERR", v8_custom_error_t::ENCODING_ERR, true)
            .static_("NOT_READABLE_ERR", v8_custom_error_t::NOT_READABLE_ERR, true)
            .static_("UNKNOWN_ERR", v8_custom_error_t::UNKNOWN_ERR, true)
            .static_("CONSTRAINT_ERR", v8_custom_error_t::CONSTRAINT_ERR, true)
            .static_("DATA_ERR", v8_custom_error_t::DATA_ERR, true)
            .static_("TRANSACTION_INACTIVE_ERR", v8_custom_error_t::TRANSACTION_INACTIVE_ERR, true)
            .static_("READONLY_ERR", v8_custom_error_t::READONLY_ERR, true)
            .static_("VERSION_ERR", v8_custom_error_t::VERSION_ERR, true)
            .static_("OPERATION_ERR", v8_custom_error_t::OPERATION_ERR, true)
            .static_("NOT_ALLOWED_ERR", v8_custom_error_t::NOT_ALLOWED_ERR, true)
            .auto_wrap_objects();
}

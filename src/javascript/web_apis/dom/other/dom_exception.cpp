module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"
#include <tuplet/tuple.hpp>
#include <v8-isolate.h>
#include <v8pp/class.hpp>


module apis.dom.dom_exception;
import apis.dom.types;
import apis.base_exception;
import ext.string;
import ext.tuple;
import js.env.module_type;


dom::dom_exception::dom_exception(
        ext::u8string&& message,
        base_exception<dom::detail::dom_exception_error_t>::exception_t type)
        : base_exception{std::move(message), std::move(type)}
{
    INIT_PIMPL;
}


auto dom::dom_exception::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    using enum detail::dom_exception_error_t;

    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<base_exception<exception_t>>()
        .ctor<ext::string&&, exception_t>()
        .static_("INDEX_SIZE_ERR", INDEX_SIZE_ERR, true)
        .static_("DOMSTRING_SIZE_ERR", DOMSTRING_SIZE_ERR, true)
        .static_("HIERARCHY_REQUEST_ERR", HIERARCHY_REQUEST_ERR, true)
        .static_("WRONG_DOCUMENT_ERR", WRONG_DOCUMENT_ERR, true)
        .static_("INVALID_CHARACTER_ERR", INVALID_CHARACTER_ERR, true)
        .static_("NO_DATA_ALLOWED_ERR", NO_DATA_ALLOWED_ERR, true)
        .static_("NO_MODIFICATION_ALLOWED_ERR", NO_MODIFICATION_ALLOWED_ERR, true)
        .static_("NOT_FOUND_ERR", NOT_FOUND_ERR, true)
        .static_("NOT_SUPPORTED_ERR", NOT_SUPPORTED_ERR, true)
        .static_("INUSE_ATTRIBUTE_ERR", INUSE_ATTRIBUTE_ERR, true)
        .static_("INVALID_STATE_ERR", INVALID_STATE_ERR, true)
        .static_("SYNTAX_ERR", SYNTAX_ERR, true)
        .static_("INVALID_MODIFICATION_ERR", INVALID_MODIFICATION_ERR, true)
        .static_("NAMESPACE_ERR", NAMESPACE_ERR, true)
        .static_("INVALID_ACCESS_ERR", INVALID_ACCESS_ERR, true)
        .static_("VALIDATION_ERR", VALIDATION_ERR, true)
        .static_("TYPE_MISMATCH_ERR", TYPE_MISMATCH_ERR, true)
        .static_("SECURITY_ERR", SECURITY_ERR, true)
        .static_("NETWORK_ERR", NETWORK_ERR, true)
        .static_("ABORT_ERR", ABORT_ERR, true)
        .static_("URL_MISMATCH_ERR", URL_MISMATCH_ERR, true)
        .static_("QUOTA_EXCEEDED_ERR", QUOTA_EXCEEDED_ERR, true)
        .static_("TIMEOUT_ERR", TIMEOUT_ERR, true)
        .static_("INVALID_NODE_TYPE_ERR", INVALID_NODE_TYPE_ERR, true)
        .static_("DATA_CLONE_ERR", DATA_CLONE_ERR, true)
        .static_("ENCODING_ERR", ENCODING_ERR, true)
        .static_("NOT_READABLE_ERR", NOT_READABLE_ERR, true)
        .static_("UNKNOWN_ERR", UNKNOWN_ERR, true)
        .static_("CONSTRAINT_ERR", CONSTRAINT_ERR, true)
        .static_("DATA_ERR", DATA_ERR, true)
        .static_("TRANSACTION_INACTIVE_ERR", TRANSACTION_INACTIVE_ERR, true)
        .static_("READONLY_ERR", READONLY_ERR, true)
        .static_("VERSION_ERR", VERSION_ERR, true)
        .static_("OPERATION_ERR", OPERATION_ERR, true)
        .static_("NOT_ALLOWED_ERR", NOT_ALLOWED_ERR, true)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

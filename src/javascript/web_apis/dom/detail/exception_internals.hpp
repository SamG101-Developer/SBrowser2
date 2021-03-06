#ifndef SBROWSER2_EXCEPTION_INTERNALS_HPP
#define SBROWSER2_EXCEPTION_INTERNALS_HPP

#include "ext/casting.hpp"
#include "ext/functional.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"
#include "ext/vector.hpp"

#define NO_CONDITION [](){return true;}
#define P(key, val) tuplet::pair{key, val}

#define verify_parent_exists(_node)                                                   \
    detail::exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR>( \
        [_parent = _node->parent_node()] {return _parent;},                           \
        "New start container must have a parent")


//#define verify_node_type_is_not(_node, ...)                                            \
//    detail::exception_internals::throw_v8_exception_formatted<INVALID_NODE_TYPE_ERR> ( \
//        [container] {return !ext::multi_cast<__VA_ARGS__>(_node);},                    \
//        ext::string{} + "Node can not be " + #__VA_ARGS__ + " types")


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
    using exception_condiditional_t = ext::function<bool()>;

    template <v8_primitive_error_t exception_type>
    auto throw_v8_exception(
            exception_condiditional_t&& condition = NO_CONDITION,
            const ext::string& exception_message = "")
            -> void;

    template <v8_custom_error_t exception_type, typename ...T>
    auto throw_v8_exception_formatted(
            exception_condiditional_t&& condition = NO_CONDITION,
            const ext::string& description = "",
            ext::vector<ext::string>&& possible_causes = {},
            ext::vector<ext::string>&& possible_fixes = {},
            T&&... object_information)
            -> void;
}


#endif //SBROWSER2_EXCEPTION_INTERNALS_HPP

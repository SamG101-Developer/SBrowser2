#ifndef SBROWSER2_EXCEPTION_INTERNALS_HPP
#define SBROWSER2_EXCEPTION_INTERNALS_HPP

#include "ext/casting.hpp"
#include "ext/functional.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(dom)

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


namespace dom::detail
{
    template <v8_primitive_error_t exception_type>
    auto throw_v8_exception(
            exception_condiditional_t&& condition = NO_CONDITION,
            const ext::string& exception_message = "")
            -> void;

    template <dom_exception_error_t exception_type, typename ...T>
    auto throw_v8_exception_formatted(
            exception_condiditional_t&& condition = NO_CONDITION,
            const ext::string& description = "",
            ext::vector<ext::string>&& possible_causes = {},
            ext::vector<ext::string>&& possible_fixes = {},
            T&&... object_information)
            -> void;
}


#endif //SBROWSER2_EXCEPTION_INTERNALS_HPP

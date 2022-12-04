#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX__TYPEDEFS_HPP

#include "ext/expected.ixx"

#include "ext/string.hpp"
#include "ext/tuple.ixx"
#include "ext/vector.hpp"


namespace css::detail
{
    enum class token_type_t;

    using token_t = ext::tuple<token_type_t, ext::string, ext::number<int>>;
    using parse_result_t = ext::expected<ext::vector<token_t>, ext::failure_t>;

    // struct syntax_error_t : ext::failure_t {};
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_SYNTAX__TYPEDEFS_HPP

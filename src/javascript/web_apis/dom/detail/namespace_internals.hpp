#ifndef SBROWSER2_NAMESPACE_INTERNALS_HPP
#define SBROWSER2_NAMESPACE_INTERNALS_HPP

#include <tuple>
#include <ext/string.hpp>

namespace dom::detail::namespace_internals
{
    inline static ext::string_view HTML   = "http://www.w3.org/1999/xhtml";
    inline static ext::string_view MATHML = "http://www.w3.org/1998/Math/MathML";
    inline static ext::string_view SVG    = "http://www.w3.org/2000/svg";
    inline static ext::string_view XLINK  = "http://www.w3.org/1999/xlink";
    inline static ext::string_view XML    = "http://www.w3.org/XML/1998/namespace";
    inline static ext::string_view XMLNS  = "http://www.w3.org/2000/xmlns/";
    inline static ext::string_view NONE   = "";

    // validation checks
    static auto validate(
            ext::string_view qualified_name)
            -> void;

    static auto validate_and_extract(
            ext::string_view namespace_,
            ext::string_view qualified_name)
            -> std::tuple<ext::string, ext::string>;
}

#endif //SBROWSER2_NAMESPACE_INTERNALS_HPP

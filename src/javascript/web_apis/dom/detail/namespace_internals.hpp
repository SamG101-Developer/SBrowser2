#ifndef SBROWSER2_NAMESPACE_INTERNALS_HPP
#define SBROWSER2_NAMESPACE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"

namespace dom::detail::namespace_internals
{
    inline static constexpr const char* HTML   = "http://www.w3.org/1999/xhtml";
    inline static constexpr const char* MATHML = "http://www.w3.org/1998/Math/MathML";
    inline static constexpr const char* SVG    = "http://www.w3.org/2000/svg";
    inline static constexpr const char* XLINK  = "http://www.w3.org/1999/xlink";
    inline static constexpr const char* XML    = "http://www.w3.org/XML/1998/namespace";
    inline static constexpr const char* XMLNS  = "http://www.w3.org/2000/xmlns/";
    inline static constexpr const char* NONE   = "";

    // validation checks
    auto validate(
            ext::string_view qualified_name)
            -> void;

    auto validate_and_extract(
            ext::string_view namespace_,
            ext::string_view qualified_name)
            -> std::tuple<ext::string, ext::string>;

    auto html_adjust_string(
            ext::string_view string,
            ext::boolean_view adjust,
            ext::boolean_view lower = true)
            -> ext::string;
}


#endif //SBROWSER2_NAMESPACE_INTERNALS_HPP

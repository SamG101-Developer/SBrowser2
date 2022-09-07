#ifndef SBROWSER2_NAMESPACE_INTERNALS_HPP
#define SBROWSER2_NAMESPACE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"

namespace dom::detail
{
    inline static constexpr const char* HTML   = "http://www.w3.org/1999/xhtml";
    inline static constexpr const char* MATHML = "http://www.w3.org/1998/Math/MathML";
    inline static constexpr const char* SVG    = "http://www.w3.org/2000/svg";
    inline static constexpr const char* XLINK  = "http://www.w3.org/1999/xlink";
    inline static constexpr const char* XML    = "http://www.w3.org/XML/1998/namespace";
    inline static constexpr const char* XMLNS  = "http://www.w3.org/2000/xmlns/";
    inline static constexpr const char* NONE   = "";

    /* N3 */
    inline static constexpr const char* DC   = "http://purl.org/dc/elements/1.1/";
    inline static constexpr const char* FOAF = "http://xmlns.com/foaf/0.1/";
    inline static constexpr const char* EX   = "http://www.example.org/#";
    inline static constexpr const char* I18N = "https://www.w3.org/ns/i18n#";
    inline static constexpr const char* RDF  = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
    inline static constexpr const char* RDFS = "http://www.w3.org/2000/01/rdf-schema#";
    inline static constexpr const char* XSD  = "http://www.w3.org/2001/XMLSchema#";

    // validation checks
    auto validate(
            ext::string_view qualified_name)
            -> void;

    auto validate_and_extract(
            ext::string_view namespace_,
            const ext::string& qualified_name)
            -> ext::tuple<ext::string, ext::string>;

    auto html_adjust_string(
            ext::string&& string,
            ext::boolean&& adjust,
            ext::boolean&& lower = true)
            -> ext::string;
}


#endif //SBROWSER2_NAMESPACE_INTERNALS_HPP

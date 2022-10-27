#ifndef SBROWSER2_NAMESPACE_INTERNALS_HPP
#define SBROWSER2_NAMESPACE_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/string.hpp"
#include "ext/tuple.hpp"

namespace dom::detail
{ // TODO : namespace these further ?
    inline static constexpr const char8_t* HTML   = u8"http://www.w3.org/1999/xhtml";
    inline static constexpr const char8_t* MATHML = u8"http://www.w3.org/1998/Math/MathML";
    inline static constexpr const char8_t* SVG    = u8"http://www.w3.org/2000/svg";
    inline static constexpr const char8_t* XLINK  = u8"http://www.w3.org/1999/xlink";
    inline static constexpr const char8_t* XML    = u8"http://www.w3.org/XML/1998/namespace";
    inline static constexpr const char8_t* XMLNS  = u8"http://www.w3.org/2000/xmlns/";
    inline static constexpr const char8_t* NONE   = u8"";

    /* N3 */
    inline static constexpr const char8_t* DC   = u8"http://purl.org/dc/elements/1.1/";
    inline static constexpr const char8_t* FOAF = u8"http://xmlns.com/foaf/0.1/";
    inline static constexpr const char8_t* EX   = u8"http://www.example.org/#";
    inline static constexpr const char8_t* I18N = u8"https://www.w3.org/ns/i18n#";
    inline static constexpr const char8_t* RDF  = u8"http://www.w3.org/1999/02/22-rdf-syntax-ns#";
    inline static constexpr const char8_t* RDFS = u8"http://www.w3.org/2000/01/rdf-schema#";
    inline static constexpr const char8_t* XSD  = u8"http://www.w3.org/2001/XMLSchema#";

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
            ext::boolean adjust,
            ext::boolean lower = true)
            -> ext::string;
}


#endif //SBROWSER2_NAMESPACE_INTERNALS_HPP

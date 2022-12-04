#ifndef SBROWSER2_NAMESPACE_INTERNALS_HPP
#define SBROWSER2_NAMESPACE_INTERNALS_HPP



#include "ext/tuple.ixx"

namespace dom::detail
{ // TODO : namespace these further ?
    inline static constexpr const ext::string::value_type* HTML   = u"http://www.w3.org/1999/xhtml";
    inline static constexpr const ext::string::value_type* MATHML = u"http://www.w3.org/1998/Math/MathML";
    inline static constexpr const ext::string::value_type* SVG    = u"http://www.w3.org/2000/svg";
    inline static constexpr const ext::string::value_type* XLINK  = u"http://www.w3.org/1999/xlink";
    inline static constexpr const ext::string::value_type* XML    = u"http://www.w3.org/XML/1998/namespace";
    inline static constexpr const ext::string::value_type* XMLNS  = u"http://www.w3.org/2000/xmlns/";
    inline static constexpr const ext::string::value_type* NONE   = u"";

    /* N3 */
    inline static constexpr const ext::string::value_type* DC   = u"http://purl.org/dc/elements/1.1/";
    inline static constexpr const ext::string::value_type* FOAF = u"http://xmlns.com/foaf/0.1/";
    inline static constexpr const ext::string::value_type* EX   = u"http://www.example.org/#";
    inline static constexpr const ext::string::value_type* I18N = u"https://www.w3.org/ns/i18n#";
    inline static constexpr const ext::string::value_type* RDF  = u"http://www.w3.org/1999/02/22-rdf-syntax-ns#";
    inline static constexpr const ext::string::value_type* RDFS = u"http://www.w3.org/2000/01/rdf-schema#";
    inline static constexpr const ext::string::value_type* XSD  = u"http://www.w3.org/2001/XMLSchema#";

    // validation checks
    auto validate(
            ext::string_view qualified_name)
            -> void;

    auto validate_and_extract(
            ext::string_view namespace_,
            ext::string_view qualified_name)
            -> ext::tuple<ext::string, ext::string>;

    auto html_adjust_string(
            ext::string&& string,
            ext::boolean adjust,
            ext::boolean lower = true)
            -> ext::string;
}


#endif //SBROWSER2_NAMESPACE_INTERNALS_HPP

module;
#include "ext/macros.hpp"


export module apis.dom_parser.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(dom_parsing)
{
    class xml_serializer;
}


DEFINE_FWD_DECL_NAMESPACE_MIXINS(dom_parsing)
{
    class inner_html;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(dom_parsing)
{
    enum class supported_type_t {
        TEXT_SLASH_HTML, TEXT_SLASH_XML, APPLICATION_SLASH_XML, APPLICATION_SLASH_XHTML_PLUS_XML,
        IMAGE_SLASH_SVG_PLUS_XML};

    using namespace_prefix_map_t = ext::map<ext::string, ext::string>;
    using generated_namespace_prefix_index_t = ext::number<int>;
}

export apis.dom_parser.types;


namespace dom_parsing::detail
{
    enum class supported_type_t {
        TEXT_SLASH_HTML, TEXT_SLASH_XML, APPLICATION_SLASH_XML, APPLICATION_SLASH_XHTML_PLUS_XML,
        IMAGE_SLASH_SVG_PLUS_XML};

    using namespace_prefix_map_t = ext::map<ext::string, ext::string>;
    using generated_namespace_prefix_index_t = ext::number<int>;
}

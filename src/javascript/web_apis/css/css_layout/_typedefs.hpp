#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT__TYPEDEFS_HPP






namespace css::detail
{
    struct layout_definition_t;
    struct document_layout_definition_t;

    enum class child_display_type_t {BLOCK, NORMAL};
    enum class layout_sizing_mode {BLOCK_LIKE, MANUAL};

    using layout_options_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_LAYOUT__TYPEDEFS_HPP

#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS__TYPEDEFS_HPP





namespace web_assembly::detail
{
    using web_assembly_instantiated_source_t = ext::map<ext::string, ext::any>;

    enum import_export_kind_t {FUNCTION, TABLE, MEMORY, GLOBAL};
    using module_export_descriptor_t = ext::map<ext::string, ext::any>;
    using module_import_descriptor_t = ext::map<ext::string, ext::any>;

    using memory_descriptor_t = ext::map<ext::string, ext::any>;

    enum class table_kind {EXTERNREF, ANYFUNC};
    using table_escriptor_t = ext::map<ext::string, ext::any>;

    using global_descriptor_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEB_ASSEMBLY_JS__TYPEDEFS_HPP

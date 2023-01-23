module;
#include "ext/macros.hpp"


export module apis.mimesniff.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(mimesniff)
{
    struct mime_type_t;
    struct resource_t;

    using resource_header_t = char8_t*;
    using byte_pattern_t = char8_t*;
    using pattern_mask_t = char8_t*;
}


struct mimesniff::detail::mime_type_t
{
    ext::string type;
    ext::string sub_type;
    ext::map<ext::string, ext::string> parameters;

    auto operator==(const mime_type_t&) const -> bool = default;
    auto operator==(ext::string_view) const -> bool;
};


struct mimesniff::detail::resource_t
{
    std::observer_ptr<mime_type_t> supplied_mime_type;
    std::observer_ptr<mime_type_t> computed_mime_type;
    ext::boolean check_for_apache_bug_flag;
    ext::boolean no_sniff_flag;
};

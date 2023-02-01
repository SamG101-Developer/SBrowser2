module;
#include "ext/macros.hpp"


export module apis.webappsec_permissions_policy.permissions_policy;
import apis.dom_object;

IMPORT_ALL_TYPES(webappsec_permissions_policy);


DEFINE_PUBLIC_CLASS(webappsec_permissions_policy, permissions_policy) final
        : virtual public dom_object
{
public constructors:
    permissions_policy();
    MAKE_PIMPL(permissions_policy);
    MAKE_V8_AVAILABLE(WINDOW);

private js_methods:
    auto allows_feature(detail::feature_name_t feature, ext::string&& origin = u"") -> ext::boolean;
    auto features() -> ext::span<detail::feature_name_t>;
    auto allowed_features() -> ext::set<ext::string>;
    auto get_allowlist_for_feature(detail::feature_name_t feature) -> ext::set<ext::string>;
};

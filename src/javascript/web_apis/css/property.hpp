#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_PROPERTY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_PROPERTY_HPP

#include "ext/boolean.hpp"
#include "ext/concepts.hpp"
#include "ext/property.hpp"
#include "ext/detail/meta_property.hpp"
namespace css {template <type_is_enum T> class css_property;}
namespace css {template <type_is_enum T> class css_meta_property;}


template <type_is_enum T>
class css::css_property : public ext::property<T>
{
public:
    // Access to the value type
    friend struct ::access_meta;
    using value_t = T;

    css_property() = default;

private:
    css::css_meta_property<T> m_meta;
};


template <type_is_enum T>
class css::css_meta_property : public ext::detail::meta_property<T>
{
private:
    ext::string m_name;
    T m_default_value;
    ext::boolean inherited;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_PROPERTY_HPP

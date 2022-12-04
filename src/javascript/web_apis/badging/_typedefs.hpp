#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING__TYPEDEFS_HPP

#include "ext/number.ixx"
#include "ext/type_traits.ixx"



namespace badging::detail
{
    enum class badge_value_t {NOTHING, FLAG};
    using badge_t = ext::variant<badge_value_t, ext::number<ulonglong>>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING__TYPEDEFS_HPP

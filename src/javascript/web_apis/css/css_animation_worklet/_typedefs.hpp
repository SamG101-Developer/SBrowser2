#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET__TYPEDEFS_HPP

#include "ext/any.hpp"
#include "ext/functional.hpp"

namespace css::detail
{
    struct animator_definition_t;
    struct document_animator_definition_t;
    struct animator_effect_t;
    struct animator_instance_t;
    struct worklet_animator_definition_t;

    using animator_instance_constructor_t = ext::function<ext::any(ext::any&& options, ext::any&& state)>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATION_WORKLET__TYPEDEFS_HPP

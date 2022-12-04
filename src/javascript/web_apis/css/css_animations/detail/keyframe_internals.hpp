#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_DETAIL_KEYFRAME_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_DETAIL_KEYFRAME_INTERNALS_HPP


#include "ext/string.hpp"
#include INCLUDE_INNER_TYPES(css/css_animations)
namespace dom::nodes {class element;}


namespace css::detail
{
    auto generate_keyframe(
            dom::nodes::element* element,
            ext::string_view name,
            ext::number<size_t> position)
            -> keyframe_t;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_ANIMATIONS_DETAIL_KEYFRAME_INTERNALS_HPP

#ifndef SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP
#define SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP

#include "dom_object.hpp"
namespace dom::mixins {class document_or_shadow_root;}

#include INCLUDE_INNER_TYPES(css/cssom)
namespace css::css_web_animations {class animation;}
namespace css::cssom::style_sheets {class css_style_sheet;}
namespace dom::nodes {class element;}

#include "dom/mixins/document_or_shadow_root_private.hpp"


class dom::mixins::document_or_shadow_root
        : public virtual dom_object
{
public constructors:
    document_or_shadow_root();
    MAKE_PIMPL(document_or_shadow_root);
    MAKE_V8_AVAILABLE;

public js_methods:
    /* [CSS_WEB_ANIMATIONS] */
    auto get_animations() -> ext::vector<css::css_web_animations::animation*>;

private js_properties:
    /* [HTML] */
    DEFINE_GETTER(active_element, nodes::element*);

    /* [POINTER_LOCK] */
    DEFINE_GETTER(pointer_lock_elment, nodes::element*);

    /* [FULLSCREEN] */
    DEFINE_GETTER(fullscreen_element, nodes::element*);

    /* [CSSOM] */
    DEFINE_GETTER(style_sheets, ext::vector<css::cssom::style_sheets::css_style_sheet*>);
    DEFINE_GETTER(adopted_style_sheets, ext::vector<css::cssom::style_sheets::css_style_sheet*>);
};


#endif //SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP

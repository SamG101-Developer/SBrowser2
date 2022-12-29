module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/macros.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.mixins.document_or_shadow_root;
import apis.dom_object;

import apis.dom.types;
import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom::mixins, document_or_shadow_root)
        : public virtual dom_object
{
public constructors:
    document_or_shadow_root();
    MAKE_PIMPL(document_or_shadow_root);
    MAKE_V8_AVAILABLE(MIXIN);

public js_methods:
    // /* [CSS_WEB_ANIMATIONS] */
    // auto get_animations() -> ext::vector<css::css_web_animations::animation*>;

private js_properties:
    /* [HTML] */
    DEFINE_GETTER(active_element, element*);

    /* [POINTER_LOCK] */
    DEFINE_GETTER(pointer_lock_elment, element*);

    /* [FULLSCREEN] */
    DEFINE_GETTER(fullscreen_element, element*);

    // /* [CSSOM] */
    // DEFINE_GETTER(style_sheets, ext::vector<css::cssom::style_sheets::css_style_sheet*>);
    // DEFINE_GETTER(adopted_style_sheets, ext::vector<css::cssom::style_sheets::css_style_sheet*>);
};

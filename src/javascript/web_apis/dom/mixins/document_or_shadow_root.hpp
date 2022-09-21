#ifndef SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP
#define SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP

#include "dom_object.hpp"
namespace dom::mixins {class document_or_shadow_root;}

#include USE_INNER_TYPES(css/cssom)
namespace css::css_web_animations {class animation;}
namespace css::cssom::style_sheets {class css_style_sheet;}
namespace dom::nodes {class element;}


class dom::mixins::document_or_shadow_root // TODO : !!!!!!!!!!!!!!!!!!!!!!!!!!!!
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(document_or_shadow_root);
    document_or_shadow_root() = default;

public js_methods:
    /* [CSS_WEB_ANIMATIONS] */
    auto get_animations() -> ext::vector<css::css_web_animations::animation*>;

public js_properties:
    /* HTML */
    ext::property<nodes::element*> active_element;

    /* POINTER_LOCK */
    ext::property<nodes::element*> pointer_lock_element;

    /* FULLSCREEN */
    ext::property<nodes::element*> fullscreen_element;

    /* CSSOM */
    ext::property<ext::vector<css::cssom::style_sheets::css_style_sheet*>> style_sheets;
    ext::property<ext::vector<css::cssom::style_sheets::css_style_sheet*>> adopted_style_sheets; // TODO

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

public cpp_properties:
    /* CSSOM */
    ext::vector<css::detail::css_style_sheet_t*> m_document_or_shadow_root_css_style_sheets;
    ext::vector<css::detail::css_style_sheet_t*> m_final_css_style_sheets;

private cpp_accessors:
    /* CSSOM */
    DEFINE_CUSTOM_GETTER(style_sheets);
};


#endif //SBROWSER2_DOCUMENT_OR_SHADOW_ROOT_HPP

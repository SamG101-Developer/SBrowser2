module;
#include "ext/macros.hpp"


export module apis.dom.mixins.document_or_shadow_root:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(dom::mixins, document_or_shadow_root)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(document_or_shadow_root);

public:
    /* [CSSOM] */
    // ext::vector<css::cssom::style_sheets::css_style_sheet_private*> m_document_or_shadow_root_css_style_sheets;
    // ext::vector<css::cssom::style_sheets::css_style_sheet_private*> m_final_css_style_sheets;
};

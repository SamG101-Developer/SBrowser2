module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.mixins.document_or_shadow_root_private;
import apis._.dom_object_private;
import ext.vector;


DEFINE_PRIVATE_CLASS(dom, document_or_shadow_root)
        : virtual dom_object_private
{
    MAKE_QIMPL(document_or_shadow_root);

    /* [CSSOM] */
    // ext::vector<css::cssom::style_sheets::css_style_sheet_private*> m_document_or_shadow_root_css_style_sheets;
    // ext::vector<css::cssom::style_sheets::css_style_sheet_private*> m_final_css_style_sheets;
};

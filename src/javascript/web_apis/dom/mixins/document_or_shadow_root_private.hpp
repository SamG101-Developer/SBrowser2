#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_DOCUMENT_OR_SHADOW_ROOT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_DOCUMENT_OR_SHADOW_ROOT_PRIVATE_HPP


#include "ext/pimpl.ixx"

#include "ext/vector.hpp"


DEFINE_PRIVATE_CLASS(dom::mixins, document_or_shadow_root)
        : virtual dom_object_private
{
    MAKE_QIMPL(document_or_shadow_root);

    /* [CSSOM] */
    ext::vector<css::cssom::style_sheets::css_style_sheet_private*> m_document_or_shadow_root_css_style_sheets;
    ext::vector<css::cssom::style_sheets::css_style_sheet_private*> m_final_css_style_sheets;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_MIXINS_DOCUMENT_OR_SHADOW_ROOT_PRIVATE_HPP

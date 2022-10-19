#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_OR_SVG_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_OR_SVG_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"


DEFINE_PRIVATE_CLASS(html::mixins, html_or_svg_element) : dom_object_private
{
    ext::string cryptographic_nonce;
    ext::boolean autofocus;
    ext::number<long> tab_index;

    ext::boolean locked_for_focus;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_HTML_OR_SVG_ELEMENT_PRIVATE_HPP

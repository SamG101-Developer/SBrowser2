#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IFRAME_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IFRAME_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "html/elements/html_element_private.hpp"
#include "html/mixins/lazy_loadable_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
namespace permissions_policy {class permissions_policy_object;}


DEFINE_PRIVATE_CLASS(html::elements, html_iframe_element)
        : html::elements::html_element_private
        , html::mixins::lazy_loadable_private
{
    /* [HTML] */
    ext::string src;
    ext::string srcdoc;
    ext::string name;
    ext::string sandbox;
    ext::string allow;
    ext::boolean allow_fullscreen;
    ext::string width;
    ext::string height;
    referrer_policy::detail::referrer_policy_t referrer_policy;
    detail::lazy_loading_t loading;

    ext::boolean current_navigation_lazy_loaded = true;
    detail::sandboxing_flag_set_t sandboxing_set;

    /* [PERMISSIONS-POLICY] */
    std::unique_ptr<permissions_policy::permissions_policy_object> permissions_policy;

    /* [FULLSCREEN] */
    ext::boolean m_iframe_fullscreen_flag;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IFRAME_ELEMENT_PRIVATE_HPP

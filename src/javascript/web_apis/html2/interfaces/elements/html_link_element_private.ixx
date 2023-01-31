module;
#include "ext/macros.hpp"


export module apis.html.html_link_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_link_element)
        : html::html_element_private
        , cssom::mixins::link_style_private
{
public:
    MAKE_QIMPL(html_link_element);

public:
    ext::string href;
    ext::optional<ext::string> cross_origin;
    ext::string rel;
    ext::string as;
    ext::vector<ext::string> rel_list;
    ext::string media;
    ext::string integrity;
    ext::string hreflang;
    ext::string type;
    ext::vector<ext::string> sizes;
    ext::string image_srcset;
    ext::string image_sizes;
    referrer_policy::detail::referrer_policy_t referrer_policy;
    ext::vector<ext::string> blocking;
    ext::boolean disabled;
};

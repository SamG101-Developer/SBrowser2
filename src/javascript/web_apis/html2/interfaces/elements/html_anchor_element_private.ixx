module;
#include "ext/macros.hpp"


export module apis.html.html_anchor_element:p;
import apis.html.html_element;


DEFINE_PRIVATE_CLASS(html, html_anchor_element)
        : html::html_element_private
        , html::mixins::html_hyperlink_element_utils_private
{
public:
    html_anchor_element_private(); // TODO : activation behaviour
    MAKE_QIMPL(html_anchor_element);

public:
    ext::string target;
    ext::string download;
    ext::string ping;
    ext::string rel;
    ext::vector<ext::string> rel_list;
    ext::string hreflang;
    ext::string type;
    referrer_policy::detail::referrer_policy_t referrer_policy;
};

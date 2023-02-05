module;
#include "ext/macros.hpp"


export module apis.html::mixins.html_hyperlink_element_utils:p;
import apis.dom_object;
import apis.types.url;


DEFINE_PRIVATE_CLASS(html::mixins, html_hyperlink_element_utils)
        : dom_object_private
{
public:
    MAKE_QIMPL(html_hyperlink_element_utils);

public:
    auto set_url() -> void;
    auto reinitialize_url() -> void;
    auto update_href() -> void;

public:
    std::unique_ptr<url::detail::url_t> url;
};

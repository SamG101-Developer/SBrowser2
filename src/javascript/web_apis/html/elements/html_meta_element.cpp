#include "html_meta_element.hpp"


html::elements::html_meta_element::html_meta_element()
{
    http_equiv._Meta._AttachConstraint(
            "content-language", "content-type", "default-style", "refresh", "set-cookie", "x-ua-compatible",
            "content-security-policy");

    HTML_CONSTRUCTOR
}

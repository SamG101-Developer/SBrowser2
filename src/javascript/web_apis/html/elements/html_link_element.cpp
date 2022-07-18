#include "html_link_element.hpp"


html::elements::html_link_element::html_link_element()
{
    rel._Meta._AttachConstraint(
            "alternate", "dns-prefetch", "icon", "manifest", "modulepreload", "next", "pingback", "preconnect",
            "prefetch", "preload", "prerender", "search", "stylesheet", "canonical");

    referrer._Meta._AttachConstraint(
            "no-referrer", "default", "unsafe-url", "origin-when-cross-origin");

    HTML_CONSTRUCTOR
}

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIME_TYPE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIME_TYPE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(html::navigators, mime_type) : virtual dom_object_private
{
    ext::string type;
    const ext::string description = u8"Portable Document Format";
    const ext::string suffixes = u8"pdf";
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIME_TYPE_PRIVATE_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_PLUGIN_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_PLUGIN_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(html::navigators, plugin) : dom_object_private
{
    ext::string name;
    const ext::string description = u8"Portable Document Format";
    const ext::string filename = u8"internal-pdf-viewer";
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_PLUGIN_PRIVATE_HPP

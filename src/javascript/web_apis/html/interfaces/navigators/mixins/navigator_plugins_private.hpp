#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_PLUGINS_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_PLUGINS_PRIVATE_HPP

#include "ext/pimpl.ixx"


#include "ext/vector.hpp"
namespace html::navigators {class plugin;}
namespace html::navigators {class mime_type;}


DEFINE_PRIVATE_CLASS(html::navigators::mixins, navigator_plugins) : virtual dom_object_private
{
    ext::vector<std::unique_ptr<plugin>> plugin_array;
    ext::vector<std::unique_ptr<mime_type>> mime_type_array;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_PLUGINS_PRIVATE_HPP

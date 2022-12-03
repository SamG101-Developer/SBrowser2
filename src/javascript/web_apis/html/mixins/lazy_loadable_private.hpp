#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include "ext/functional.ixx"


DEFINE_PRIVATE_CLASS(html::mixins, lazy_loadable) : virtual dom_object_private
{
    ext::function<void()> lazy_load_resumption_steps;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_MIXINS_LAZY_LOADABLE_PRIVATE_HPP

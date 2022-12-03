#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_COWL_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_COWL_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"
namespace webappsec::cowl {class cowl;}


DEFINE_PRIVATE_CLASS(webappsec::cowl, cowl) : dom_object_private
{
    MAKE_QIMPL(cowl);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_COWL_PRIVATE_HPP

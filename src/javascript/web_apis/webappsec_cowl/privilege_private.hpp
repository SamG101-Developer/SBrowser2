#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_PRIVILEGE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_PRIVILEGE_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
namespace webappsec::cowl {class privilege;}

namespace webappsec::cowl {class label;}


DEFINE_PRIVATE_CLASS(webappsec::cowl, privilege) : dom_object_private
{
    MAKE_QIMPL(privilege);

    std::unique_ptr<label> internal_privilege_label;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_PRIVILEGE_PRIVATE_HPP

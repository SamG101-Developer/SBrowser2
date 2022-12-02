#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABELED_OBJECT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABELED_OBJECT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"
namespace webappsec::cowl {class labeled_object;}

#include "ext/memory.ixx"
namespace webappsec::cowl {class label;}


DEFINE_PRIVATE_CLASS(webappsec::cowl, labeled_object) : dom_object_private
{
    MAKE_QIMPL(labeled_object);

    std::observer_ptr<label> confidentiality_label;
    std::observer_ptr<label> integrity_label;
    std::unique_ptr<void> protected_object;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABELED_OBJECT_PRIVATE_HPP

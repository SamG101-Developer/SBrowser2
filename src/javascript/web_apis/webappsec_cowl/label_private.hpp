#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(webappsec_cowl)
#include "ext/set.hpp"


DEFINE_PRIVATE_CLASS(webappsec::cowl, label) : dom_object_private
{
    MAKE_QIMPL(label);

    detail::label_set_t label_set;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_LABEL_PRIVATE_HPP

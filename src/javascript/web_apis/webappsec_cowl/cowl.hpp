#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_COWL_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_COWL_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
#include "ext/singleton.hpp"
namespace webappsec::cowl {class cowl;}
namespace webappsec::cowl {class cowl_private;}

// Other Includes & Forward Declarations

namespace webappsec::cowl {class label;}
namespace webappsec::cowl {class privilege;}


class webappsec::cowl::cowl
        : virtual public dom_object
        , ext::singleton<cowl>
{
public constructors:
    cowl();
    MAKE_PIMPL(cowl);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_STATIC_GETTER(confidentiality, label*);
    DEFINE_STATIC_GETTER(integrity, label*);
    DEFINE_STATIC_GETTER(privilege, privilege*);

    DEFINE_STATIC_SETTER(confidentiality, label*);
    DEFINE_STATIC_SETTER(integrity, label*);
    DEFINE_STATIC_SETTER(privilege, privilege*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_COWL_HPP

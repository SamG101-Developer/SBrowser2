#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP

#include "dom_object.hpp"
namespace html::other {class location;}
namespace html::other {class location_private;}


class html::other::location
        : public virtual dom_object
{
public constructors:
    location();
    MAKE_PIMPL(location);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_LOCATION_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace html::other {class history;}
namespace html::other {class history_private;}

// Other Includes & Forward Declarations


class html::other::history
        : public dom_object
{
public constructors:
    history();
    MAKE_PIMPL(history);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_OTHER_HISTORY_HPP

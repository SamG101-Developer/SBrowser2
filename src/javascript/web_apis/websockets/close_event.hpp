#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_CLOSE_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_CLOSE_EVENT_HPP

// Inheritance Includes & This Class
#include "dom/events/event.hpp"
namespace websockets {class close_event;}
namespace websockets {class close_event_private;}

// Other Includes & Forward Declarations


class websockets::close_event
        : public dom::events::event
{
public constructors:
    close_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(close_event);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_CLOSE_EVENT_HPP

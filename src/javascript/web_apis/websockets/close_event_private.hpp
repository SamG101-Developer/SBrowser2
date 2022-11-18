#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_CLOSE_EVENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_CLOSE_EVENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/events/event_private.hpp"
namespace websockets {class close_event;}


DEFINE_PRIVATE_CLASS(websockets, close_event) : dom::events::event_private
{
    MAKE_QIMPL(close_event);

    ext::boolean was_clean;
    ext::number<ushort> code;
    ext::string reason;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBSOCKETS_CLOSE_EVENT_PRIVATE_HPP

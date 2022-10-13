#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_EVENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_EVENT_HPP

// Inheritance Includes & This Class
#include "service_workers/events/extendable_event.hpp"
namespace push_api {class push_event;}
namespace push_api {class push_event_private;}

// Other Includes & Forward Declarations
namespace push_api {class push_message_data;}


class push_api::push_event
        : public service_workers::events::extendable_event
{
public constructors:
    push_event(ext::string&& event_type, ext::map<ext::string, ext::any>&& event_init = {});
    MAKE_PIMPL(push_event);
    MAKE_V8_AVAILABLE;

public:
    DEFINE_GETTER(data, push_message_data*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PUSH_API_PUSH_EVENT_HPP

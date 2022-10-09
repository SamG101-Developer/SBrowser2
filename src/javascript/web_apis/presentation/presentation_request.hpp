#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_REQUEST_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_REQUEST_HPP

// Inheritance Includes & This Class
#include "dom/nodes/event_target.hpp"
namespace presentation {class presentation_request;}
namespace presentation {class presentation_request_private;}

// Other Includes & Forward Declarations
#include "ext/promise.hpp"
#include "ext/span.hpp"
namespace presentation {class presentation_connection;}
namespace presentation {class presentation_availablility;}


class presentation::presentation_request
        : public dom::nodes::event_target
{
public constructors:
    presentation_request(ext::string&& url);
    presentation_request(ext::vector_span<ext::string> urls);

    DOM_CTORS(presentation_request);
    MAKE_PIMPL(presentation_request);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto start() -> ext::promise<presentation_connection>;
    auto reconnect() -> ext::promise<presentation_connection>;
    auto get_availability() -> presentation_availablility;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_REQUEST_HPP

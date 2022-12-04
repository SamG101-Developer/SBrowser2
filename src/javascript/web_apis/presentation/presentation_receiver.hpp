#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_RECEIVER_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_RECEIVER_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace presentation {class presentation_receiver;}
namespace presentation {class presentation_receiver_private;}

// Other Includes & Forward Declarations

#include "ext/span.hpp"
namespace presentation {class presentation_connection;}


class presentation::presentation_receiver
        : virtual public dom_object
{
public constructors:
    MAKE_PIMPL(presentation_receiver);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(connection_list, ext::promise<ext::vector_span<presentation_connection*>>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_RECEIVER_HPP

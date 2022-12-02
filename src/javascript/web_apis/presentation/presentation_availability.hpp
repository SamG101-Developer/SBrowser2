#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_AVAILABILITY_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_AVAILABILITY_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace presentation {class presentation_availability;}
namespace presentation {class presentation_availability_private;}

// Other Includes & Forward Declarations
#include "ext/boolean.ixx"


class presentation::presentation_availability
        : virtual public dom_object
{
public constructors:
    presentation_availability();
    ~presentation_availability();
    MAKE_PIMPL(presentation_availability);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(value, ext::boolean);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_AVAILABILITY_HPP

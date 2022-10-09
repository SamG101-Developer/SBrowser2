#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace presentation {class presentation;}
namespace presentation {class presentation_private;}

// Other Includes & Forward Declarations
namespace presentation {class presentation_request;}
namespace presentation {class presentation_receiver;}


class presentation::presentation
        : public dom_object
{
public constructors:
    presentation();
    MAKE_PIMPL(presentation);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(presentation_request, presentation_request*);
    DEFINE_GETTER(presentation_receiver, presentation_receiver*);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION_PRESENTATION_HPP

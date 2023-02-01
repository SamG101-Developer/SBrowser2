#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_CONCURRENT_HARDWARE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_CONCURRENT_HARDWARE_HPP

// Inheritance Includes & This Class

namespace html::navigators::mixins {class navigator_concurrent_hardware;}
namespace html::navigators::mixins {class navigator_concurrent_hardware_private;}

// Other Includes & Forward Declarations


class html::navigators::mixins::navigator_concurrent_hardware
        : virtual public dom_object
{
public constructors:
    navigator_concurrent_hardware();
    MAKE_PIMPL(navigator_concurrent_hardware);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(navigator_concurrent_hardware, ext::number<ulonglong>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_CONCURRENT_HARDWARE_HPP

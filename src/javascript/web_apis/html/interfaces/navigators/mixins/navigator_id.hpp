#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_ID_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_ID_HPP

// Inheritance Includes & This Class

namespace html::navigators::mixins {class navigator_id;}
namespace html::navigators::mixins {class navigator_id_private;}

// Other Includes & Forward Declarations


class html::navigators::mixins::navigator_id
        : virtual public dom_object
{
public constructors:
    navigator_id();
    MAKE_PIMPL(navigator_id);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(app_code_name, ext::string) {return u8"Mozilla";}
    DEFINE_GETTER(app_name, ext::string) {return u8"Netscape";}
    DEFINE_GETTER(app_version, ext::string);
    DEFINE_GETTER(platform, ext::string);
    DEFINE_GETTER(product, ext::string) {return u8"Gecko";}
    DEFINE_GETTER(product_sub, ext::string);
    DEFINE_GETTER(user_agent, ext::string);
    DEFINE_GETTER(vendor, ext::string);
    DEFINE_GETTER(oscpu, ext::string);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_ID_HPP

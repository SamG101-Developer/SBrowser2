#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_LANGUAGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_LANGUAGE_HPP

// Inheritance Includes & This Class

namespace html::navigators::mixins {class navigator_language;}
namespace html::navigators::mixins {class navigator_language_private;}

// Other Includes & Forward Declarations


class html::navigators::mixins::navigator_language
        : virtual public dom_object
{
public constructors:
    navigator_language();
    MAKE_PIMPL(navigator_language);
    MAKE_V8_AVAILABLE;

public js_properties:
    DEFINE_GETTER(language, ext::string);
    DEFINE_GETTER(languages, ext::vector<ext::string>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_NAVIGATORS_MIXINS_NAVIGATOR_LANGUAGE_HPP

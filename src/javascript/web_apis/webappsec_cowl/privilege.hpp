#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_PRIVILEGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_PRIVILEGE_HPP

// Inheritance Includes & This Class

namespace webappsec::cowl {class privilege;}
namespace webappsec::cowl {class privilege_private;}

// Other Includes & Forward Declarations
namespace webappsec::cowl {class label;}


class webappsec::cowl::privilege
        : virtual public dom_object
{
public constructors:
    privilege();
    MAKE_PIMPL(privilege);
    MAKE_V8_AVAILABLE;

private js_methods:
    static auto fresh_privilege() -> std::unique_ptr<privilege>;
    auto as_label() -> label*;
    auto combine(privilege* other) -> std::unique_ptr<privilege>;
    auto delegate(label* other_label) -> std::unique_ptr<privilege>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_PRIVILEGE_HPP

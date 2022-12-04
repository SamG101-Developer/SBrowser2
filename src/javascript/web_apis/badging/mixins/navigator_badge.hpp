#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP

#include "dom_object.hpp"
namespace badging::mixins {class navigator_badge;}
namespace badging::mixins {class navigator_badge_private;}



#include "ext/type_traits.ixx"


class badging::mixins::navigator_badge
        : public virtual dom_object
{
public constructors:
    navigator_badge();
    MAKE_PIMPL(navigator_badge);
    MAKE_V8_AVAILABLE(SECURE);

public js_methods:
    auto set_app_badge(ext::number<ulonglong> contents) -> ext::promise<void>;
    auto clear_app_badge() -> ext::promise<void>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP

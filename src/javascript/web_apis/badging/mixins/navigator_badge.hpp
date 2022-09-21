#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP

#include "dom_object.hpp"
namespace badging::mixins {class navigator_badge;}

#include "ext/promise.hpp"
#include "ext/number.hpp"
#include "ext/type_traits.hpp"


class badging::mixins::navigator_badge
        : public virtual dom_object
{
public constructors:
    navigator_badge() = default;

public js_methods:
    auto set_app_badge(ext::number<ulonglong> contents) -> ext::promise<void>;
    auto clear_app_badge() -> ext::promise<void>;

private cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP

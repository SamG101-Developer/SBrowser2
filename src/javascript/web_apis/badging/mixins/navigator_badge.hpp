#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP

#include "dom_object.hpp"
namespace badging::mixins {class navigator_badge;}

#include <future>
#include "ext/number.hpp"
#include "ext/type_traits.hpp"


class badging::mixins::navigator_badge
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(navigator_badge);
    navigator_badge() = default;

public js_methods:
    auto set_app_badge(const ext::number<ulonglong>& contents) -> std::promise<void>;
    auto clear_app_badge() -> std::promise<void>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP
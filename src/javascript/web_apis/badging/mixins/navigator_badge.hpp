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
    DOM_CTORS(navigator_badge);
    navigator_badge() = default;

public js_methods:
    auto set_app_badge(const ext::number<ulonglong>& contents) -> ext::promise<void>;
    auto clear_app_badge() -> ext::promise<void>;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BADGING_NAVIGATOR_BADGE_HPP

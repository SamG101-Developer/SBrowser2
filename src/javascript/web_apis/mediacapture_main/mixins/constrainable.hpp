#pragma once
#ifndef SBROWSER2_CONSTRAINABLE_HPP
#define SBROWSER2_CONSTRAINABLE_HPP

#include "dom_object.hpp"
namespace mediacapture::main::mixins {class constrainable;}

#include "ext/promise.hpp"
#include "ext/map.hpp"
#include USE_INNER_TYPES(mediacapture_main)


class mediacapture::main::mixins::constrainable
        : public virtual dom_object
{
public js_methods:
    _EXT_NODISCARD auto get_capabilities() const -> detail::capabilities_t;
    _EXT_NODISCARD auto get_constraints() const -> detail::constraints_t;
    _EXT_NODISCARD auto get_settings() const -> detail::settings_t;
    auto apply_constraints(detail::constraints_t&& constraints = {}) -> ext::promise<void>;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected js_slots:
    detail::capabilities_t s_capabilities;
    detail::constraints_t s_constraints;
    detail::settings_t s_settings;
};


#endif //SBROWSER2_CONSTRAINABLE_HPP

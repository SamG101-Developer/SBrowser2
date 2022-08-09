#pragma once
#ifndef SBROWSER2_CONSTRAINABLE_HPP
#define SBROWSER2_CONSTRAINABLE_HPP

#include "dom_object.hpp"
namespace mediacapture::main::mixins {class constrainable;}

#include <future>
#include "ext/map.hpp"


class mediacapture::main::mixins::constrainable
        : public virtual dom_object
{
public js_methods:
    _EXT_NODISCARD auto get_capabilities() const -> ext::map<ext::string, ext::any>;
    _EXT_NODISCARD auto get_constraints() const -> ext::map<ext::string, ext::any>;
    _EXT_NODISCARD auto get_settings() const -> ext::map<ext::string, ext::any>;
    auto apply_constraints(ext::map_view<ext::string, ext::any> constraints = {}) -> std::promise<void>;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

protected js_slots:
    ext::map<ext::string, ext::any> s_capabilities;
    ext::map<ext::string, ext::any> s_constraints;
    ext::map<ext::string, ext::any> s_settings;
};


#endif //SBROWSER2_CONSTRAINABLE_HPP

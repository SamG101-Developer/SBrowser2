#pragma once
#ifndef SBROWSER2_CONSTRAINABLE_HPP
#define SBROWSER2_CONSTRAINABLE_HPP

#include "dom_object.hpp"
namespace mediacapture::main::mixins {class constrainable;}
namespace mediacapture::main::mixins {class constrainable_private;}



#include INCLUDE_INNER_TYPES(mediacapture_main)


class mediacapture::main::mixins::constrainable
        : public virtual dom_object
{
public constructors:
    constrainable();
    MAKE_PIMPL(constrainable);
    MAKE_V8_AVAILABLE;

public js_methods:
    _EXT_NODISCARD auto get_capabilities() const -> detail::capabilities_t;
    _EXT_NODISCARD auto get_constraints() const -> detail::constraints_t;
    _EXT_NODISCARD auto get_settings() const -> detail::settings_t;
    auto apply_constraints(detail::constraints_t&& constraints = {}) -> ext::promise<void>;
};


#endif //SBROWSER2_CONSTRAINABLE_HPP

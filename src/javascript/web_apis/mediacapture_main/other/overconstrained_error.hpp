#pragma once
#ifndef SBROWSER2_OVERCONSTRAINED_ERROR_HPP
#define SBROWSER2_OVERCONSTRAINED_ERROR_HPP

#include "dom/other/dom_exception.hpp"
namespace mediacapture::main::other {class overconstrained_error;}


class mediacapture::main::other::overconstrained_error
        : public dom::other::dom_exception
{
public constructors:
    explicit overconstrained_error(ext::string&& constraint, ext::string&& message = "");

public js_properties:
    ext::property<ext::string> constraint;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_OVERCONSTRAINED_ERROR_HPP

#pragma once
#ifndef SBROWSER2_OVERCONSTRAINED_ERROR_HPP
#define SBROWSER2_OVERCONSTRAINED_ERROR_HPP


namespace mediacapture::main::other {class overconstrained_error;}
namespace mediacapture::main::other {class overconstrained_error_private;}


class mediacapture::main::other::overconstrained_error
        : public dom::other::dom_exception
{
public constructors:
    overconstrained_error(ext::string&& constraint, ext::string&& message = u"");
    MAKE_PIMPL(overconstrained_error);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(constraint, ext::string);
};


#endif //SBROWSER2_OVERCONSTRAINED_ERROR_HPP

#include "overconstrained_error.hpp"
#include "dom/other/dom_exception.hpp"


mediacapture::main::other::overconstrained_error::overconstrained_error(
        ext::string&& constraint,
        ext::string&& message)
        : dom::other::dom_exception{std::move(message), std::bit_cast<dom_exception_error_t>(0)}
{}

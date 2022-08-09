#include "overconstrained_error.hpp"
#include "dom/other/dom_exception.hpp"


mediacapture::main::other::overconstrained_error::overconstrained_error(
        ext::string&& constraint,
        ext::string&& message)
        : dom::other::dom_exception{std::move(message), std::bit_cast<v8_custom_error_t>(0)}
{}

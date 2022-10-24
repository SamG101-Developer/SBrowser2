#include "overconstrained_error.hpp"
#include "overconstrained_error_private.hpp"

#include "dom/_typedefs.hpp"
#include "dom/other/dom_exception.hpp"


mediacapture::main::other::overconstrained_error::overconstrained_error(
        ext::string&& constraint,
        ext::string&& message)
        : dom::other::dom_exception{std::move(message), dom::detail::dom_exception_error_t::OVERCONSTRAINED_ERR}
{
    INIT_PIMPL(overconstrained_error);

    ACCESS_PIMPL(overconstrained_error);
    d->constraint = std::move(constraint);
}

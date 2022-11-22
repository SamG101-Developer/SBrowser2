#include "csp_violation_report_body.hpp"
#include "csp_violation_report_body_private.hpp"

#include "webappsec_csp/detail/reporting_internals.hpp"
#include "webappsec_csp/detail/violation_internals.hpp"

#include <magic_enum.hpp>


auto webappsec::csp::csp_violation_report_body::get_blocked_uri() const -> ext::string
{
    ACCESS_PIMPL(const csp_violation_report_body);
    ext::holds_alternative<ext::string>(d->violation->resource)
            ? magic_enum::enum_name(ext::unsafe_get<0>(d->violation->resource))
            : detail::strip_url_for_violation_report(*ext::unsafe_get<1>(d->violation->resource));
}

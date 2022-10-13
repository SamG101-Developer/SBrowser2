#include "report.hpp"
#include "report_private.hpp"

#include "url/detail/url_internals.hpp"


auto reporting::report::get_type() const -> ext::string_view
{
    ACCESS_PIMPL(const report);
    return d->type;
}


auto reporting::report::get_url() const -> ext::string
{
    ACCESS_PIMPL(const report);
    return url::detail::url_serializer(*d->url);
}


auto reporting::report::get_body() const -> report_body*
{
    ACCESS_PIMPL(const report);
    return d->body.get();
}

module;
#include "ext/macros.hpp"


module apis.reporting.report;
import apis.reporting.report_body;

import apis.url.detail;

import ext.core;


auto reporting::report::get_type() const -> ext::string_view
{
    ACCESS_PIMPL;
    return d->report->type;
}


auto reporting::report::get_url() const -> ext::string
{
    ACCESS_PIMPL;
    return url::detail::url_serializer(*d->report->url);
}


auto reporting::report::get_body() const -> report_body*
{
    ACCESS_PIMPL;
    return d->report->body.get();
}

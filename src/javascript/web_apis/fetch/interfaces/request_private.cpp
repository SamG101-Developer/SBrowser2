module apis.fetch.request:p;
import apis.fetch.detail;

import ext.core;


auto fetch::request_private::mime_type() const -> ext::string
{
    return detail::extract_mime_type(request->header_list);
}


auto fetch::request_private::body() const -> detail::body_t&
{
    return *request->body;
}

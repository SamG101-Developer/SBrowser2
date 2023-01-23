module apis.fetch.response:p;
import apis.fetch.detail;

import ext.core;


auto fetch::response_private::mime_type() const -> ext::string
{
    return detail::extract_mimetype(response->header_list);
}


auto fetch::response_private::body() const -> detail::body_t&
{
    return *response->body;
}

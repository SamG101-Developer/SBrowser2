#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_HPP

#include "base_exception.ixx"
namespace html::basic_media {class media_error;}
namespace html::basic_media {class media_error_private;}

#include INCLUDE_INNER_TYPES(html)


class html::basic_media::media_error
        : public base_exception<detail::media_error_type_t>
{
public constructors:
    media_error(ext::string&& message, exception_t type);
    MAKE_PIMPL(media_error);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_HPP

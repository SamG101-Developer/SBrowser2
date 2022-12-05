#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "base_exception_private.ixx"

#include INCLUDE_INNER_TYPES(html)


DEFINE_PRIVATE_CLASS(html::basic_media, media_error) : base_exception_private<detail::media_error_type_t> {};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_PRIVATE_HPP

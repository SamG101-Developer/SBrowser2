#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "ext/vector_like.ixx"



DEFINE_PRIVATE_CLASS(html::basic_media, time_ranges)
        : virtual dom_object_private
        , ext::vector_like_linked_private<ext::pair<ext::number<double>, ext::number<double>>>
{};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_PRIVATE_HPP

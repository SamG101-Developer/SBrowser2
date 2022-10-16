#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_HPP

#include "dom_object.hpp"
#include "ext/vector_like.hpp"
namespace html::basic_media {class time_ranges;}
namespace html::basic_media {class time_ranges_private;}


class html::basic_media::time_ranges
        : public virtual dom_object
        , ext::vector_like_linked<ext::pair<ext::number<double>, ext::number<double>>>
{
public constructors:
    time_ranges();
    MAKE_PIMPL(time_ranges);
    MAKE_V8_AVAILABLE;

public js_methods:
    _EXT_NODISCARD auto start(ext::number<long> index) const -> ext::number<double>;
    _EXT_NODISCARD auto end(ext::number<long> index) const -> ext::number<double>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_HPP

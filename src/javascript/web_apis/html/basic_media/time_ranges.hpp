#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_HPP

#include "dom_object.hpp"
namespace html::basic_media {class time_ranges;}


class html::basic_media::time_ranges
        : public dom_object
{
public constructors:
    DOM_CTORS(time_ranges);
    time_ranges() = default;

public js_methods:
    auto start(const ext::number<double>& index) -> ext::number<double>;
    auto end(const ext::number<double>& index) -> ext::number<double>;

public js_properties:
    ext::property<ext::number<ulong>> length;

private cpp_accessors:
    DEFINE_GETTER(length);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_HPP

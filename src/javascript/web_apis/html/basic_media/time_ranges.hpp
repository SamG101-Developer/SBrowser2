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
    time_ranges();

public js_methods:
    auto start(ext::number<long> index) -> ext::number<double>;
    auto end(ext::number<long> index) -> ext::number<double>;

private js_properties:
    ext::property<ext::number<ulong>> length;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::vector<ext::pair<ext::number<double>, ext::number<double>>> m_ranges;

private js_properties:
    DEFINE_CUSTOM_GETTER(length);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TIME_RANGES_HPP

#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_HPP

#include "dom_object.hpp"
namespace html::basic_media {class abstract_track;}

#include INCLUDE_INNER_TYPES(html)


class html::basic_media::abstract_track
        : public virtual dom_object
{
public constructors:
    abstract_track() = default;

public js_properties:
    ext::property<ext::string> id;
    ext::property<html::detail::text_track_kind_t> kind;
    ext::property<ext::string> label;
    ext::property<ext::string> language;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_ABSTRACT_TRACK_HPP

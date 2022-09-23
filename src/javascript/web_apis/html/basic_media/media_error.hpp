#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_HPP

#include "dom_object.hpp"
namespace html::basic_media {class media_error;}


class html::basic_media::media_error
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(media_error);
    media_error() = default;

public js_static_constants:
    constexpr static const ext::number<ushort> MEDIA_ERR_ABORTED = 1;
    constexpr static const ext::number<ushort> MEDIA_ERR_NETWORK = 2;
    constexpr static const ext::number<ushort> MEDIA_ERR_DECODE = 3;
    constexpr static const ext::number<ushort> MEDIA_ERR_SRC_NOT_SUPPORTED = 4;

public cpp_methods:
    auto to_v8(v8::Isolate* isolate) const && -> ext::any override;

private js_properties:
    ext::property<ext::number<ushort>> code;
    ext::property<ext::string> message;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_MEDIA_ERROR_HPP

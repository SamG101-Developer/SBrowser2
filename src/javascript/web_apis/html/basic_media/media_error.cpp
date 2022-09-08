#include "media_error.hpp"


auto html::basic_media::media_error::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<media_error>{isolate}
        .inherit<dom_object>()
        .static_("MEDIA_ERR_ABORTED", media_error::MEDIA_ERR_ABORTED, true)
        .static_("MEDIA_ERR_NETWORK", media_error::MEDIA_ERR_NETWORK, true)
        .static_("MEDIA_ERR_DECODE", media_error::MEDIA_ERR_DECODE, true)
        .static_("MEDIA_ERR_SRC_NOT_SUPPORTED", media_error::MEDIA_ERR_SRC_NOT_SUPPORTED, true)
        .var("code", &media_error::code, true)
        .var("message", &media_error::message, true)
        .auto_wrap_objects();
}

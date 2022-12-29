#include "media_error.hpp"

#include INCLUDE_INNER_TYPES(html)


auto html::basic_media::media_error::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    using enum detail::media_error_type_t;

    decltype(auto) conversion = v8pp::class_<media_error>{isolate}
        .inherit<dom_object>()
        .static_("MEDIA_ERR_ABORTED", MEDIA_ERR_ABORTED, true)
        .static_("MEDIA_ERR_NETWORK", MEDIA_ERR_NETWORK, true)
        .static_("MEDIA_ERR_DECODE", MEDIA_ERR_DECODE, true)
        .static_("MEDIA_ERR_SRC_NOT_SUPPORTED", MEDIA_ERR_SRC_NOT_SUPPORTED, true)
        .auto_wrap_objects();

    return std::move(conversion);
}

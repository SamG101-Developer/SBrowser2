module;
#include "ext/macros.hpp"


export module apis.media_capabilities.media_capability_private;
import apis.dom_object;


DEFINE_ media::capabilities::media_capabilities
        : public virtual dom_object
{
public constructors:
    media_capabilities() = default;
    MAKE_PIMPL(media_capabilities);
    MAKE_V8_AVAILABLE;

public js_methods:
    auto decoding_info(detail::media_decoding_configuration_t&& configuration) -> ext::promise<detail::media_capabilities_decoding_info_t>;
    auto encoding_info(detail::media_encoding_configuration_t&& configuration) -> ext::promise<detail::media_capabilities_encoding_info_t>;
};

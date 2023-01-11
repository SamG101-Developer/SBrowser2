module;
#include "ext/macros.hpp"


export module apis.media_capabilities.media_capabilities;
import apis.dom_object;

import apis.media_capabilities.types;
import ext.js;


DEFINE_PUBLIC_CLASS(media_capabilities, media_capabilities) final
        : public virtual dom_object
{
public constructors:
    media_capabilities() = default;
    MAKE_PIMPL(media_capabilities);
    MAKE_V8_AVAILABLE(WINDOW | WORKER);

public js_methods:
    auto decoding_info(detail::media_decoding_configuration_t&& configuration) -> ext::promise<detail::media_capabilities_decoding_info_t>;
    auto encoding_info(detail::media_encoding_configuration_t&& configuration) -> ext::promise<detail::media_capabilities_encoding_info_t>;
};

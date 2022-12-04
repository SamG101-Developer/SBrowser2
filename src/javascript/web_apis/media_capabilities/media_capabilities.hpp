#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_MEDIA_CAPABILITIES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_MEDIA_CAPABILITIES_HPP

#include "dom_object.hpp"
namespace media::capabilities {class media_capabilities;}
namespace media::capabilities {class media_capabilities_private;}

#include INCLUDE_INNER_TYPES(media_capabilities)



class media::capabilities::media_capabilities
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


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_MEDIA_CAPABILITIES_HPP

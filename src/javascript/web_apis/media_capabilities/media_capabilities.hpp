#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_MEDIA_CAPABILITIES_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_MEDIA_CAPABILITIES_HPP

#include "dom_object.hpp"
namespace media::capabilities {class media_capabilities;}

#include <future>
#include "media_capabilities/_typedefs.hpp"


class media::capabilities::media_capabilities
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(media_capabilities);

    auto decoding_info(
            detail::media_decoding_configuration_t&& configuration)
            -> std::promise<detail::media_capabilities_decoding_info_t>;

    auto encoding_info(
            detail::media_decoding_configuration_t&& configuration)
            -> std::promise<detail::media_capabilities_decoding_info_t>;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_CAPABILITIES_MEDIA_CAPABILITIES_HPP

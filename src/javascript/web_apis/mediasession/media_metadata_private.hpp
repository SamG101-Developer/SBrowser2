#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_METADATA_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_METADATA_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom_object_private.hpp"

#include INCLUDE_INNER_TYPES(mediasession)
#include "ext/memory.hpp"
#include "ext/string.hpp"
namespace mediasession {class media_session;}


DEFINE_PRIVATE_CLASS(mediasession, media_metadata)
        : virtual dom_object_private
{
    MAKE_QIMPL(media_metadata);

    std::observer_ptr<media_session> media_session;
    ext::string title;
    ext::string artist;
    ext::string album;
    ext::vector<detail::media_image_t> artowrk_imagesl
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_METADATA_PRIVATE_HPP

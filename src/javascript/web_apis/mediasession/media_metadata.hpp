#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_METADATA_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_METADATA_HPP

// Inheritance Includes & This Class
#include "dom_object.hpp"
namespace mediasession {class media_metadata;}
namespace mediasession {class media_metadata_private;}

// Other Includes & Forward Declarations
#include INCLUDE_INNER_TYPES(mediasession)
#include "ext/vector.hpp"


class mediasession::media_metadata
        : virtual public dom_object
{
public constructors:
    media_metadata(detail::media_metadata_init_t&& init = {});
    MAKE_PIMPL(media_metadata);
    MAKE_V8_AVAILABLE(WINDOW);

public js_properties:
    DEFINE_GETTER(title, ext::string);
    DEFINE_GETTER(artist, ext::string);
    DEFINE_GETTER(album, ext::string);
    DEFINE_GETTER(artwork, ext::vector<detail::media_image_t>);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIASESSION_MEDIA_METADATA_HPP

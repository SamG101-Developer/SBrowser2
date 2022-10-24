#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_HPP

#include "dom_object.hpp"
#include "html/mixins/transferable.hpp"
namespace media::source {class media_source_handle;}
namespace media::source {class media_source_handle_private;}


class media::source::media_source_handle
        : public virtual dom_object
{
public constructors:
    media_source_handle();
    MAKE_PIMPL(media_source_handle);
    MAKE_TRANSFERABLE(media_source_handle);
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_HPP

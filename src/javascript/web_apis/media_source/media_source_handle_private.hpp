#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom_object_private.hpp"

#include "ext/boolean.ixx"
#include "ext/memory.ixx"
namespace media::source {class media_source;}


DEFINE_PRIVATE_CLASS(media::source, media_source_handle) : virtual dom_object_private
{
    ext::boolean has_ever_been_assigned_as_srcobject;
    ext::boolean detached;

    std::observer_ptr<media_source> media_source;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE_MEDIA_SOURCE_HANDLE_PRIVATE_HPP

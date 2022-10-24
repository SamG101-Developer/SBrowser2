#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_OTHER_MEDIA_STREAM_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_OTHER_MEDIA_STREAM_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/event_target_private.hpp"

#include "ext/set.hpp"
namespace mediacapture::main {class media_stream_track;}


DEFINE_PRIVATE_CLASS(mediacapture::main, media_stream) : dom::nodes::event_target_private
{
    ext::string id;
    ext::set<media_stream_track*> track_set;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_MAIN_OTHER_MEDIA_STREAM_PRIVATE_HPP

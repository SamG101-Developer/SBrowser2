#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/basic_media/abstract_track_private.hpp"

#include INCLUDE_INNER_TYPES(html)
namespace html::basic_media {class text_track_cue;}


DEFINE_PRIVATE_CLASS(html::basic_media, text_track) : html::basic_media::abstract_track_private
{
    ext::string in_band_metadata_track_dispatch_type;
    detail::track_mode_t mode;

    ext::vector<std::unique_ptr<text_track_cue>> text_track_cues;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_BASIC_MEDIA_TEXT_TRACK_PRIVATE_HPP

module;
#include "ext/macros.hpp"


export module apis.html.audio_track:p;
import apis.html.abstract_track;

import ext.boolean;


DEFINE_PRIVATE_CLASS(html, audio_track) : html::basic_media::abstract_track_private
{
    ext::boolean enabled;
};

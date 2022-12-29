module;
#include "ext/macros/pimpl.hpp"


export module apis.html.audio_track_private;
import apis.html.abstract_track_private;

import ext.boolean;


DEFINE_PRIVATE_CLASS(html, audio_track) : html::basic_media::abstract_track_private
{
    ext::boolean enabled;
};

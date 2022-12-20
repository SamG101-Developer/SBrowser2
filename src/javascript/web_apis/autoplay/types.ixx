module;
#include "ext/macros/pimpl.hpp"


export module apis.autoplay.types;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(autoplay)
{
    enum class autoplay_policy_t {ALLOWED, ALLOWED_MUTED, DISALLOWED};
    enum class autoplay_policy_media_type_t {MEDIA_ELEMENT, AUDIO_CONTEXT};
}

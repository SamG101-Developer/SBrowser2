module;
#include "ext/macros.hpp"


export module apis.media_source.types;


DEFINE_FWD_DECL_NAMESPACE(media_source)
{
    class media_source;
    class media_source_handle;
    class source_buffer;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(media_source)
{
    enum class ready_state_t {CLOSED, OPEN, ENDED};
    enum class end_of_stream_error_t {NETWORK, DECODE};
    enum class append_mode_t {SEGMENTS, SEQUENCE};
}

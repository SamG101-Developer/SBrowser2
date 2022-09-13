#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE__TYPEDEFS_HPP


namespace media::detail
{
    enum class ready_state_t {CLOSED, OPEN, ENDED};
    enum class end_of_stream_error_t {NETWORK, DECODE};
    enum class append_mode_t {SEGMENTS, SEQUENCE};
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIA_SOURCE__TYPEDEFS_HPP

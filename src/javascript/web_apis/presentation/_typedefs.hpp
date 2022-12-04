#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION__TYPEDEFS_HPP




namespace presentation::detail
{
    struct presentation_display_t;

    enum class presentation_connection_state_t {CONNECTING, CONNECTED, CLOSED, TERMINATED};
    enum presentation_message_t {TEXT, BINARY};
    enum class presentation_connection_close_reason {ERROR, CLOSED, WENTAWAY};

    using presentation_id_t = ext::string;
    using presentation_message_data_t = ext::string;
    using presentation_close_message_t = ext::string;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_PRESENTATION__TYPEDEFS_HPP

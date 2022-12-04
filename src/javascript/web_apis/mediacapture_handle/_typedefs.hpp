#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE__TYPEDEFS_HPP





namespace mediacapture::detail
{
    enum class capture_action_t {NEXT, PREVIOUS, FIRST, LAST};

    using capture_handle_config_t = ext::map<ext::string, ext::any>;
    using capture_handle_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_HANDLE__TYPEDEFS_HPP

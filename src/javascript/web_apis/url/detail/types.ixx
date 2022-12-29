module;
#include "ext/macros/macros.hpp"


export module apis.url.types;
import apis.file_api.types;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE(url)
{
    class url;
    class url_search_params;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(url)
{
    struct url_t;

    enum class special_scheme_t {FTP, FILE, HTTP, HTTPS, WS, WSS};
    enum class state_override_t {
        SCHEME_START_STATE, SCHEME_STATE, NO_SCHEME_STATE, SPECIAL_RELATIVE_OR_AUTHORITY_STATE, PATH_OR_AUTHORITY_STATE,
        RELATIVE_STATE, RELATIVE_SLASH_STATE, SPECIAL_AUTHORITY_SLASHES_STATE, SPECIAL_AUTHORITY_IGNORE_SLASHES_STATE,
        AUTHORITY_STATE, HOST_STATE, HOSTNAME_STATE, PORT_STATE, FILE_STATE, FILE_SLASH_STATE, FILE_HOST_STATE,
        PATH_START_STATE, PATH_STATE, OPAQUE_PATH_STATE, QUERY_STATE, FRAGMENT_STATE
    };

    using domain_t = ext::string;
};


struct url::detail::url_t
{
    url_t(ext::string&& url_string);
    url_t(const url_t&);

    ext::string scheme;
    ext::string username;
    ext::string password;
    domain_t host;

    ext::number<short> port;
    ext::vector<ext::string> path;
    ext::string query;
    ext::string fragment;

    std::unique_ptr<file_api::detail::blob_url_entry_t> blob_url_entry {nullptr};
    std::unique_ptr<void> object {nullptr};

    auto operator*() -> ext::string; // TODO {return url_serializer(*this);}
};

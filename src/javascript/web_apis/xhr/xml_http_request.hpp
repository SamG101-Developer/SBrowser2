#ifndef SBROWSER2_XML_HTTP_REQUEST_HPP
#define SBROWSER2_XML_HTTP_REQUEST_HPP

#include "xml_http_request_event_target.hpp"
namespace xhr {class xml_http_request;}

#include "fetch/detail/body_internals.hpp"
#include "fetch/detail/http_internals.hpp"
#include "fetch/detail/header_internals.hpp"

#include INCLUDE_INNER_TYPES(url)

namespace fetch {class response;}
namespace xhr {class xml_http_request_upload;}
namespace webappsec::cowl {class labeled_object;}


class xhr::xml_http_request
        : public xml_http_request_event_target
{
public constructors:
    xml_http_request();

public enums:
    enum response_type_t {ARRAYBUFFER, BLOB, DOCUMENT, JSON, TEXT};

private js_static_constants:
    constexpr static const ext::number<ushort> UNSENT = 0;
    constexpr static const ext::number<ushort> OPENED = 1;
    constexpr static const ext::number<ushort> HEADERS_RECEIVED = 2;
    constexpr static const ext::number<ushort> LOADING = 3;
    constexpr static const ext::number<ushort> DONE = 4;

private js_methods:
    auto open(ext::string_view method, ext::string_view url, ext::optional<ext::boolean> async, ext::string_view username = "", ext::string_view password = "");
    auto set_request_header(ext::string_view name, ext::string_view value, ext::number_view<ulong> timeout, ext::boolean_view with_credentials) -> void;
    auto send(dom::nodes::document* document = nullptr) -> void;
    auto abort() -> void;

    auto get_response_header(ext::string name) -> ext::string;
    auto get_all_response_header() -> ext::string_view;
    auto override_mimetype(ext::string_view mime) -> void;

    /* [WEBAPPSEC-COWL] TODO : See other extensions to XHR spec */
    auto send(webappsec::cowl::labeled_object* labeled_object) -> void;

private js_properties:
    ext::property<ext::number<ushort>> ready_state;

    ext::property<ext::string> response_url;
    ext::property<ext::number<ushort>> status;
    ext::property<ext::string> status_text;

    ext::property<ext::any> response;
    ext::property<ext::string> response_type; // TODO : constrain
    ext::property<ext::string> response_text;
    ext::property<dom::nodes::document*> response_xml; // TODO : unique_ptr? (check if custom getter exists or not)

private cpp_properties:
    xml_http_request_upload& m_upload_object;
    ext::number<ushort> m_state;
    ext::number<uint> m_send_flag;
    ext::boolean m_cross_origin_credentials;
    url::detail::url_t url;
    fetch::detail::method_t m_method;
    fetch::detail::headers_t m_author_request_headers;
    fetch::detail::body_t& m_request_body;

    ext::boolean m_synchronous_flag;
    ext::boolean m_upload_complete_flag;
    ext::boolean m_upload_listener_flag;
    ext::boolean m_timed_out_flag;

    fetch::response& m_response;
    ext::string m_received_bytes;
    response_type_t m_response_type;
    fetch::response& response_object; // TODO : type
    fetch::detail::fetch_controller_t& m_fetch_controller;
    ext::string mime_type;
};


#endif //SBROWSER2_XML_HTTP_REQUEST_HPP

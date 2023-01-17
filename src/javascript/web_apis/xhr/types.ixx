module;
#include "ext/macros.hpp"


export module apis.xhr.types;


DEFINE_FWD_DECL_NAMESPACE(xhr)
{
    class form_data;
    class progress_event;
    class xml_http_request;
    class xml_http_request_event_target;
    class xml_http_request_upload;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(xhr)
{
    enum xml_http_request_response_type_t {/* [WEBAPPSEC-COWL] */ LABELED_JSON};
}

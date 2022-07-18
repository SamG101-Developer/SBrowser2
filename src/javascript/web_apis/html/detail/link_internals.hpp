#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "fetch/_typedefs.hpp"
namespace dom::nodes {class document;}
namespace html::elements {class html_link_element;}
namespace fetch::detail::request_internals {class internal_request;}
namespace fetch::detail::response_internals {class internal_response;}

namespace html::detail::link_internals
{
    enum class phase_t {PRE_MEDIA, MEDIA};

    struct link_processing_options;

    auto custom_fetch_and_process_linked_resource(
            elements::html_link_element* element,
            fetch::detail::request_internals::internal_request& request)
            -> ext::boolean;

    auto default_fetch_and_process_linked_resource(
            elements::html_link_element* element)
            -> void;

    auto create_link_options(
            elements::html_link_element* element)
            -> link_processing_options;

    auto create_link_request(
            link_processing_options&& options)
            -> fetch::detail::request_internals::internal_request;

    auto extract_links_from_headers(
            const fetch::headers_t& headers)
            -> ext::vector<ext::string>;

    auto process_link_headers(
            dom::nodes::document*,
            fetch::detail::response_internals::internal_response& response,
            phase_t phase)
            -> void;

    auto apply_link_options_from_parsed_header_attributes(
            ext::map<ext::string, ext::any>& options,
            ext::map<ext::string, ext::any>&& attributes)
            -> void;

    auto process_early_hint_headers(
            fetch::detail::response_internals::internal_response& response,
            v8::Local<v8::Object> reserved_environment)
            -> void;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP

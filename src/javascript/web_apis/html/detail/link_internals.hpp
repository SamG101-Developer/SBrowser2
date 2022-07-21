#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "fetch/_typedefs.hpp"
#include "url/url.hpp"
namespace dom::nodes {class document;}
namespace dom::nodes {class window;}
namespace html::detail::context_internals {struct browsing_context;}
namespace html::elements {class html_element;}
namespace html::elements {class html_link_element;}
namespace fetch::detail::request_internals {class internal_request;}
namespace fetch::detail::request_internals {enum class credentials_t;}
namespace fetch::detail::request_internals {enum class destination_t;}
namespace fetch::detail::request_internals {enum class mode_t;}
namespace fetch::detail::response_internals {class internal_response;}


namespace html::detail::link_internals
{
    template <typename T>
    concept linkable_element = requires
    {
        requires std::is_base_of_v<elements::html_element, T>;
        T::referrer_policy;
    };

    using response_available_function_t = ext::function<void(fetch::detail::response_internals::internal_response*)>;

    enum class phase_t {PRE_MEDIA, MEDIA};

    struct link_processing_options {/* TODO : attributes */};
    struct preload_key;
    struct preload_entry;

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

    auto cannot_navigate(
            const elements::html_element* element)
            -> ext::boolean;

    auto get_elements_noopener(
            const linkable_element auto* element,
            ext::string_view target)
            -> ext::boolean;

    auto follow_hyperlink(
            const linkable_element auto* element,
            ext::string_view hyperlink_suffix = "")
            -> void;

    auto allowed_to_download(
            context_internals::browsing_context* initiator_browsing_context,
            context_internals::browsing_context* instantiator_browsing_context)
            -> ext::boolean;

    auto download_hyperlink(
            elements::html_element* element,
            ext::string_view hyperlink_suffix)
            -> void;

    auto filename_for_resource_download(
            /* TODO : parameters */)
            -> ext::string;

    auto consume_preloaded_resource(
            dom::nodes::window* window,
            url::url_object& url,
            fetch::detail::request_internals::destination_t destination,
            fetch::detail::request_internals::mode_t mode,
            fetch::detail::request_internals::credentials_t credentials,
            ext::string_view integrity_metadata,
            response_available_function_t&& on_response_available)
            -> ext::boolean;

    auto create_preload_key(
            fetch::detail::request_internals::internal_request* request)
            -> preload_key;

    auto preload(
            link_processing_options&& options,
            response_available_function_t&& process_response)
            -> void;
}


struct html::detail::link_internals::preload_key
{
    url::url_object url;
    fetch::detail::request_internals::destination_t destination;
    fetch::detail::request_internals::mode_t mode;
    fetch::detail::request_internals::credentials_t credentials_mode;
};


struct html::detail::link_internals::preload_entry
{
    ext::string integrity_data;
    fetch::detail::response_internals::internal_response* response;
    response_available_function_t on_response_available;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP

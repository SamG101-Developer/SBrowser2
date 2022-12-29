#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP




#include "ext/vector.hpp"

#include INCLUDE_INNER_TYPES(fetch)
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(url)

namespace dom::nodes {class document;}
namespace dom::nodes {class window;}
namespace html::elements {class html_element;}
namespace html::elements {class html_link_element;}


namespace html::detail
{
    template <typename T>
    concept linkable_element = requires
    {
        requires std::is_base_of_v<elements::html_element, T>;
        T::referrer_policy;
    };

    auto custom_fetch_and_process_linked_resource(
            elements::html_link_element* element,
            fetch::detail::request_t& request)
            -> ext::boolean;

    auto default_fetch_and_process_linked_resource(
            elements::html_link_element* element)
            -> void;

    auto create_link_options(
            elements::html_link_element* element)
            -> link_processing_options;

    auto create_link_request(
            link_processing_options&& options)
            -> fetch::detail::request_t;

    auto extract_links_from_headers(
            const fetch::detail::headers_t& headers)
            -> ext::vector<ext::string>;

    auto process_link_headers(
            dom::nodes::document*,
            fetch::detail::response_t& response,
            phase_t phase)
            -> void;

    auto apply_link_options_from_parsed_header_attributes(
            ext::map<ext::string, ext::any>& options,
            ext::map<ext::string, ext::any>&& attributes)
            -> void;

    auto process_early_hint_headers(
            fetch::detail::response_t& response,
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

    auto user_has_preference_to_download_hyperlink()
            -> ext::boolean;

    auto filename_for_resource_download(
            /* TODO : parameters */)
            -> ext::string;

    auto consume_preloaded_resource(
            dom::nodes::window* window,
            url::detail::url_t& url,
            fetch::detail::destination_t destination,
            fetch::detail::mode_t mode,
            fetch::detail::credentials_t credentials,
            ext::string_view integrity_metadata,
            detail::response_available_function_t&& on_response_available)
            -> ext::boolean;

    auto create_preload_key(
            fetch::detail::request_t* request)
            -> preload_key;

    auto preload(
            link_processing_options&& options,
            response_available_function_t&& process_response)
            -> void;
}


struct html::detail::preload_key
{
    url::detail::url_t url;
    fetch::detail::destination_t destination;
    fetch::detail::mode_t mode;
    fetch::detail::credentials_t credentials_mode;
};


struct html::detail::preload_entry
{
    ext::string integrity_data;
    fetch::detail::response_t* response;
    response_available_function_t on_response_available;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LINK_INTERNALS_HPP

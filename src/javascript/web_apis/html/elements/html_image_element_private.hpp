#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "html/elements/html_element_private.hpp"
#include "html/mixins/lazy_loadable_private.hpp"

#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)


DEFINE_PRIVATE_CLASS(html::elements, html_image_element)
        : html::elements::html_element_private
        , html::mixins::lazy_loadable_private
{
    ext::string alt;
    ext::string src;
    ext::string srcset;
    ext::string sizes;
    detail::cross_origin_settings_attribute_t cross_origin;
    ext::string use_map;
    ext::boolean is_map;
    referrer_policy::detail::referrer_policy_t referrer_policy;
    detail::lazy_loading_t loading;
    detail::image_decoding_hint_t decoding;
    // TODO : maybe width and height (otherwise get and set from unique-ptr<Widget>::width() etc

    std::unique_ptr<html_image_element> dimension_attribute_source;
    std::unique_ptr<detail::image_request_t> current_request;
    std::unique_ptr<detail::image_request_t> pending_request;

    ext::string last_selected_source;
    ext::set<html::detail::image_source_t*> source_set;
    ext::number<int> source_size;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_PRIVATE_HPP

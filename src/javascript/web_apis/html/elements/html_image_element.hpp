#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/lazy_loadable.hpp"
namespace html::elements {class html_image_element;}

#include "ext/promise.hpp"
#include "ext/set.hpp"
#include INCLUDE_INNER_TYPES(html)
#include INCLUDE_INNER_TYPES(referrer_policy)
namespace dom::nodes {class window_proxy;}

#define _IMAGES_SUPPORTED 1 /* TODO : move to another file where all MACRO configs are stored */


class html::elements::html_image_element
        : public html_element
        , public mixins::lazy_loadable
{
public constructors:
    html_image_element();

public js_methods:
    auto decode() -> ext::promise<void>;

private js_properties:
    ext::property<ext::string> alt;
    ext::property<ext::string> src;
    ext::property<ext::string> srcset;
    ext::property<ext::string> sizes;
    ext::property<ext::string> cross_origin;
    ext::property<ext::string> use_map;
    ext::property<referrer_policy::detail::referrer_policy_t> referrer_policy;
    ext::property<detail::lazy_loading_t> loading;
    ext::property<ext::string> decoding;
    ext::property<ext::string> current_src;

    ext::property<ext::number<ulong>> width;
    ext::property<ext::number<ulong>> height;
    ext::property<ext::number<ulong>> natural_width;
    ext::property<ext::number<ulong>> natural_height;

    ext::property<ext::boolean> is_map;
    ext::property<ext::boolean> complete;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    std::unique_ptr<html_image_element> m_dimension_attribute_source;
    std::unique_ptr<detail::image_request_t> m_current_request;
    std::unique_ptr<detail::image_request_t> m_pending_request;

    ext::string m_last_selected_source;
    ext::set<html::detail::image_source_t*> m_source_set;
    ext::number<int> m_source_size;

private js_properties:
    DEFINE_CUSTOM_GETTER(current_src);
    DEFINE_CUSTOM_GETTER(srcset);
    DEFINE_CUSTOM_GETTER(width);
    DEFINE_CUSTOM_GETTER(height);
    DEFINE_CUSTOM_GETTER(natural_width);
    DEFINE_CUSTOM_GETTER(natural_height);
    DEFINE_CUSTOM_GETTER(complete);

    DEFINE_CUSTOM_SETTER(loading);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP

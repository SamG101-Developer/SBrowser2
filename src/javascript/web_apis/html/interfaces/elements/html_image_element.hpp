#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/lazy_loadable.hpp"
namespace html::elements {class html_image_element;}
namespace html::elements {class html_image_element_private;}


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
    DOM_CTORS(html_image_element);
    MAKE_PIMPL(html_image_element);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto decode() -> ext::promise<void>;

private js_properties:
    DEFINE_GETTER(alt, ext::string_view);
    DEFINE_GETTER(src, ext::string_view);
    DEFINE_GETTER(srcset, ext::string_view);
    DEFINE_GETTER(sizes, ext::string_view);
    DEFINE_GETTER(cross_origin, detail::cross_origin_settings_attribute_t);
    DEFINE_GETTER(use_map, ext::string_view);
    DEFINE_GETTER(is_map, ext::boolean);
    DEFINE_GETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
    DEFINE_GETTER(loading, detail::lazy_loading_t);
    DEFINE_GETTER(decoding, detail::image_decoding_hint_t);
    DEFINE_GETTER(width, ext::number<ulong>);
    DEFINE_GETTER(height, ext::number<ulong>);
    DEFINE_GETTER(natural_width, ext::number<ulong>);
    DEFINE_GETTER(natural_height, ext::number<ulong>);
    DEFINE_GETTER(current_src, ext::string_view);
    DEFINE_GETTER(complete, ext::boolean);

    DEFINE_SETTER(alt, ext::string);
    DEFINE_SETTER(src, ext::string);
    DEFINE_SETTER(srcset, ext::string);
    DEFINE_SETTER(sizes, ext::string);
    DEFINE_SETTER(cross_origin, detail::cross_origin_settings_attribute_t);
    DEFINE_SETTER(use_map, ext::string);
    DEFINE_SETTER(is_map, ext::boolean);
    DEFINE_SETTER(referrer_policy, referrer_policy::detail::referrer_policy_t);
    DEFINE_SETTER(loading, detail::lazy_loading_t);
    DEFINE_SETTER(decoding, detail::image_decoding_hint_t);
    DEFINE_SETTER(width, ext::number<ulong>);
    DEFINE_SETTER(height, ext::number<ulong>);

};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP

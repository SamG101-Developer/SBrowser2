#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/lazy_loadable.hpp"
namespace html::elements {class html_image_element;}

#include <future>
namespace dom::nodes {class window_proxy;}
namespace html::detail::image_internals {struct image_request;}
namespace html::detail::image_internals {struct image_source;}
namespace html::detail::image_internals {auto update_image_data(elements::html_image_element* element, ext::boolean_view restart_animation_flag) -> void;}

#define _IMAGES_SUPPORTED 1 /* TODO : move to another file where all MACRO configs are stored */


class html::elements::html_image_element
        : public html_element
        , public mixins::lazy_loadable
{
public friends:
    friend auto detail::image_internals::update_image_data(
            elements::html_image_element* element,
            ext::boolean_view restart_animation_flag)
            -> void;

public constructors:
    html_image_element();

public js_methods:
    auto decode() -> std::promise<void>;

public js_properties:
    ext::property<ext::string, _T> alt;
    ext::property<ext::string, _T> src;
    ext::property<ext::string, _T> srcset;
    ext::property<ext::string, _T> sizes;
    ext::property<ext::string, _T> cross_origin;
    ext::property<ext::string, _T> use_map;
    ext::property<ext::string, _T> referrer_policy;
    ext::property<ext::string, _T> loading;
    ext::property<ext::string, _T> decoding;
    ext::property<ext::string, _F> current_src;

    ext::property<ext::number<ulong>, _T> width;
    ext::property<ext::number<ulong>, _T> height;
    ext::property<ext::number<ulong>, _F> natural_width;
    ext::property<ext::number<ulong>, _F> natural_height;

    ext::property<ext::boolean, _T> is_map;
    ext::property<ext::boolean, _F> complete;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    std::unique_ptr<html_image_element> m_dimension_attribute_source;
    std::unique_ptr<detail::image_internals::image_request> m_current_request;
    std::unique_ptr<detail::image_internals::image_request> m_pending_request;

    ext::string m_last_selected_source;
    ext::set<html::detail::image_internals::image_source*> m_source_set;
    ext::number<int> m_source_size;

private cpp_accessors:
    auto get_current_src() const -> ext::string;
    auto get_src_set() const -> ext::string;
    auto get_width() const -> ext::number<ulong>;
    auto get_height() const -> ext::number<ulong>;
    auto get_natural_width() const -> ext::number<ulong>;
    auto get_natural_height() const -> ext::number<ulong>;
    auto get_complete() const -> ext::boolean;

    auto set_loading(ext::string_view val) -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_ELEMENTS_HTML_IMAGE_ELEMENT_HPP

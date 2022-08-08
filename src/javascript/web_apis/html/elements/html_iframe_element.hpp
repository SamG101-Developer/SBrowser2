#pragma once
#ifndef SBROWSER2_HTML_IFRAME_ELEMENT_HPP
#define SBROWSER2_HTML_IFRAME_ELEMENT_HPP

#include "html/elements/html_element.hpp"
#include "html/mixins/lazy_loadable.hpp"
namespace html::elements {class html_iframe_element;}

namespace dom::nodes {class document;}
namespace dom::nodes {class window_proxy;}
namespace permissions_policy {class permissions_policy_object;}


class html::elements::html_iframe_element
        : public html_element
        , public mixins::lazy_loadable
{
public constructors:
    html_iframe_element();

public js_methods:
    auto get_svg_document() -> dom::nodes::document*;

public js_properties:
    /* HTML */
    ext::property<ext::string, _T> src;
    ext::property<ext::string, _T> srcdoc;
    ext::property<ext::string, _T> name;
    ext::property<ext::string, _F> sandbox;
    ext::property<ext::string, _T> allow;
    ext::property<ext::boolean, _T> allow_fullscreen;

    ext::property<ext::string, _T> width;
    ext::property<ext::string, _T> height;
    ext::property<ext::string, _T> referrer_policy;
    ext::property<ext::string, _T> loading;

    ext::property<dom::nodes::document*> content_document;
    ext::property<dom::nodes::window_proxy*> content_window;

    /* PERMISSIONS_POLICY */
    ext::property<std::unique_ptr<permissions_policy::permissions_policy_object>> permissions_policy;

public cpp_methods:
    auto to_v8(v8::Isolate *isolate) const && -> ext::any override;

private cpp_properties:
    ext::boolean m_current_navigation_lazy_loaded = ext::boolean::FALSE();

private cpp_accessors:
    auto get_content_document() const -> dom::nodes::document*;
    auto get_content_window() const -> dom::nodes::window_proxy*;
    auto set_sandbox(ext::string_view val) -> void;
    auto set_loading(ext::string_view val) -> void;
};


#endif //SBROWSER2_HTML_IFRAME_ELEMENT_HPP

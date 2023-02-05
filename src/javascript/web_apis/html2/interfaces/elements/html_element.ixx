module;
#include "ext/macros.hpp"


export module apis.html.html_element;
import apis.dom.element;


DEFINE_PUBLIC_CLASS(html, html_element) final
        : public dom::element
        , html::mixins::element_content_editable
        , html::mixins::html_or_svg_element
{
public constructors:
    html_element();
    MAKE_PIMPL(html_element);
    MAKE_V8_AVAILABLE();

private js_methods:
    auto click() -> void;
    auto attach_internals() -> std::unique_ptr<element_internals>;
    auto show_popover() -> void;
    auto hide_popover() -> void;
    auto toggle_popover() -> void;

private js_properties:
    DEFINE_GETTER(title, ext::string_view);
    DEFINE_GETTER(lang, ext::string_view);
    DEFINE_GETTER(translate, ext::boolean);
    DEFINE_GETTER(dir, ext::string_view);

    DEFINE_GETTER(hidden, ext::variant<ext::boolean, ext::number<double>, ext::string_view>);
    DEFINE_GETTER(inert, ext::boolean)
    DEFINE_GETTER(access_key, ext::string_view);
    DEFINE_GETTER(access_key_label, ext::string_view);
    DEFINE_GETTER(draggable, ext::boolean);
    DEFINE_GETTER(spellcheck, ext::boolean);
    DEFINE_GETTER(autocapitalize, ext::string_view);

    DEFINE_GETTER(inner_text, ext::string);
    DEFINE_GETTER(outer_text, ext::string);

    DEFINE_GETTER(popover, ext::string_view)


    DEFINE_SETTER(title, ext::string);
    DEFINE_SETTER(lang, ext::string);
    DEFINE_SETTER(translate, ext::boolean);
    DEFINE_SETTER(dir, ext::string);

    DEFINE_SETTER(hidden, ext::variant<ext::boolean, ext::number<double>, ext::string>);
    DEFINE_SETTER(inert, ext::boolean)
    DEFINE_SETTER(access_key, ext::string);
    DEFINE_SETTER(draggable, ext::boolean);
    DEFINE_SETTER(spellcheck, ext::boolean);
    DEFINE_SETTER(autocapitalize, ext::string);

    DEFINE_SETTER(inner_text, ext::string);
    DEFINE_SETTER(outer_text, ext::string);

    DEFINE_SETTER(popover, ext::string)
};

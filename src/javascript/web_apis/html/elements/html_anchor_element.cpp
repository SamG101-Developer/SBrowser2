#include "html_anchor_element.hpp"

#include "javascript/environment/reflection.hpp"

#include "dom/detail/node_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/events/event.hpp"

#include "html/detail/link_internals.hpp"


html::elements::html_anchor_element::html_anchor_element()
{
    bind_get(text);
    bind_set(text);

    m_dom_behaviour.activation_behaviour = [this](dom::events::event* event)
    {
        JS_REALM_GET_RELEVANT(this)
        return_if(!reflect_has_attribute_value(this, "href", this_relevant));

        ext::string hyperlink_suffix;
        // TODO : distance from mouse click, requires UIEvents
        ext::number<int> x {};
        ext::number<int> y {};
        hyperlink_suffix = char(0x003f) + ext::to_string(x) + char(0x002c) + ext::to_string(y);

        reflect_has_attribute_value(this, "download", this_relevant) && !download().empty() // TODO : or expressed preference to download
                ? detail::download_hyperlink(this, hyperlink_suffix)
                : detail::follow_hyperlink(this, hyperlink_suffix);
    };

    HTML_CONSTRUCTOR
}


auto html::elements::html_anchor_element::get_text()
        const -> ext::string
{
    return dom::detail::descendant_text_content(this);
}


auto html::elements::html_anchor_element::set_text(
        ext::string_view val)
        -> void
{
    return dom::detail::string_replace_all(val, this);
}


auto html::elements::html_anchor_element::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<html_anchor_element>{isolate}
            .ctor<>()
            .inherit<html_element>()
            .inherit<mixins::html_hyperlink_element_utils>()
            .var("target", &html_anchor_element::target, false)
            .var("download", &html_anchor_element::download, false)
            .var("ping", &html_anchor_element::ping, false)
            .var("rel", &html_anchor_element::rel, false)
            .var("hreflang", &html_anchor_element::hreflang, false)
            .var("type", &html_anchor_element::type, false)
            .var("text", &html_anchor_element::text, false)
            .var("referrerPolicy", &html_anchor_element::referrer_policy, false)
            .auto_wrap_objects();
}


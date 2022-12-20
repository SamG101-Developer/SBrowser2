module;
#include "ext/macros/annotations.hpp"
#include "ext/macros/constructors.hpp"
#include "ext/macros/pimpl.hpp"
#include "ext/macros/property.hpp"
#include "javascript/macros/expose.hpp"


export module apis.dom.text;
import apis.dom.character_data;
import apis.dom.mixins.slottable;

import ext.core;
import js.env.module_type;


DEFINE_PUBLIC_CLASS(dom, text)
        : public dom::character_data
        , public dom::slottable
{
public friends:
    friend class dom::node;
    friend class dom::dom_implementation;
    friend class html::html_option_element;

public constructors:
    text(ext::string&& new_data = u8"");
    DOM_CTORS(text);
    MAKE_PIMPL(text);
    MAKE_V8_AVAILABLE(WINDOW);

public js_methods:
    auto split_text(ext::number<ulong> offset) -> std::unique_ptr<text>;

private js_properties:
    DEFINE_GETTER(node_type, ext::number<ushort>) override {return TEXT_NODE;}
    DEFINE_GETTER(node_name, ext::string) override;
    DEFINE_GETTER(whole_text, ext::string);
};

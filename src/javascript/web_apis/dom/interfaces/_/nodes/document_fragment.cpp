module;
#include "ext/macros/custom_operator.hpp"
#include "ext/macros/macros.hpp"
#include "javascript/macros/errors.hpp"
#include "javascript/macros/expose.hpp"


module apis.dom.document_fragment;
import apis.dom.document_fragment_private;
import apis.dom.types;

import ext.core;

import js.env.module_type;
import js.env.realms;
import js.env.slots;


dom::document_fragment::document_fragment()
{
    INIT_PIMPL;
}


auto dom::document_fragment::get_node_name() const -> ext::string
{
    // The 'node_name' getter returns the fixed string "#document-origin". Apply custom element reactions to this
    // getter.
    _CE_REACTIONS_METHOD_DEF
        return u"#document-fragment";
    _CE_REACTIONS_METHOD_EXE
}


auto dom::document_fragment::get_node_value() const -> ext::string
{
    // The 'node_value' getter returns the fixed string "". Apply custom element reactions to this getter.
    _CE_REACTIONS_METHOD_DEF
        return u"";
    _CE_REACTIONS_METHOD_EXE
}


auto dom::document_fragment::get_text_content() const -> ext::string
{
    // The 'text_content' getter returns the 'descendant_text_content' of this node
    ACCESS_PIMPL;
    return d->descendant_text_content();
}


auto dom::document_fragment::set_text_content(ext::string new_text_content) -> ext::view_of_t<ext::string>
{
    // The 'text_content' setter runs a 'string_replace_all' detail method that replaces all the textual content of
    // nodes under this node in the tree (descendants of this DocumentFragment only)
    d->string_replace_all(new_text_content);
    return new_text_content;
}


auto dom::document_fragment::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<node>()
        .inherit<non_element_parent_node>()
        .inherit<parentable_node>()
        .ctor<>()
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

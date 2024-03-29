module;
#include "ext/macros.hpp"


module apis.dom.node_filter;
import apis.dom.node;

import ext.core;
import js.env.module_type;


dom::node_filter::node_filter()
{
    INIT_PIMPL;

    ACCESS_PIMPL;
    d->accept_node_callback = [](node*) {return FILTER_ACCEPT;};
}


auto dom::node_filter::get_accept_node() const -> ext::view_of_t<accept_callback_t>
{
    // The 'accept_node' getter returns the equivalent 'accept_node' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->accept_node_callback;
}


auto dom::node_filter::set_accept_node(accept_callback_t&& new_accept_node) -> ext::view_of_t<accept_callback_t&&>
{
    // The 'accept_node' setter returns the equivalent 'accept_node' attribute value that is stored in the private
    // class, after being set to the 'new_accept_node' value.
    ACCESS_PIMPL;
    d->accept_node_callback = std::move(new_accept_node);
}


auto dom::node_filter::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .static_("FILTER_ACCEPT", node_filter::FILTER_ACCEPT, true)
        .static_("FILTER_SKIP", node_filter::FILTER_SKIP, true)
        .static_("FILTER_REJECT", node_filter::FILTER_REJECT, true)
        .static_("SHOW_ELEMENT", node_filter::SHOW_ELEMENT, true)
        .static_("SHOW_ATTRIBUTE", node_filter::SHOW_ATTRIBUTE, true)
        .static_("SHOW_TEXT", node_filter::SHOW_TEXT, true)
        .static_("SHOW_CDATA_SECTION", node_filter::SHOW_CDATA_SECTION, true)
        .static_("SHOW_PROCESSING_INSTRUCTION", node_filter::SHOW_PROCESSING_INSTRUCTION, true)
        .static_("SHOW_COMMENT", node_filter::SHOW_COMMENT, true)
        .static_("SHOW_DOCUMENT", node_filter::SHOW_DOCUMENT, true)
        .static_("SHOW_DOCUMENT_TYPE", node_filter::SHOW_DOCUMENT_TYPE, true)
        .static_("SHOW_DOCUMENT_FRAGMENT", node_filter::SHOW_DOCUMENT_FRAGMENT, true)
        .static_("SHOW_ALL", node_filter::SHOW_ALL, true)
        .property("acceptNode", &node_filter::get_accept_node, &node_filter::set_accept_node)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

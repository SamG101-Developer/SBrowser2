module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


module apis.dom.abstract_iterator;
import apis.dom.abstract_iterator_private;
import ext.core;
import js.env.module_type;


dom::abstract_iterator::abstract_iterator()
{
    INIT_PIMPL; ACCESS_PIMPL;

    d->filter = nullptr;
    d->root = nullptr;
    d->what_to_show = 0;
}


auto dom::abstract_iterator::get_filter() const -> node_filter*
{
    // The 'filter' getter returns the equivalent 'filter' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->filter.get();
}


auto dom::abstract_iterator::get_root() const -> node*
{
    // The 'root' getter returns the equivalent 'root' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->root.get();
}


auto dom::abstract_iterator::get_what_to_show() const -> ext::number<ulong>
{
    // The 'what_to_show' getter returns the equivalent 'what_to_show' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL;
    return d->what_to_show;
}


auto dom::abstract_iterator::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("filter", &abstract_iterator::get_filter)
        .property("root", &abstract_iterator::get_root)
        .property("whatToShow", &abstract_iterator::get_what_to_show)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

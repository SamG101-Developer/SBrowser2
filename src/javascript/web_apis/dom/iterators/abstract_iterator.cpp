#include "abstract_iterator.hpp"
#include "abstract_iterator_private.hpp"

#include "dom/detail/traversal_internals.hpp"
#include "dom/iterators/node_filter.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "dom/other/dom_implementation.hpp"


dom::node_iterators::abstract_iterator::abstract_iterator()
{
    INIT_PIMPL(abstract_iterator);
    ACCESS_PIMPL(abstract_iterator);

    d->filter = nullptr;
    d->root = nullptr;
    d->what_to_show = 0;
}


auto dom::node_iterators::abstract_iterator::get_filter() const -> node_filter*
{
    // The 'filter' getter returns the equivalent 'filter' attribute value that is stored in the private class.
    ACCESS_PIMPL(const abstract_iterator);
    return d->filter.get();
}


auto dom::node_iterators::abstract_iterator::get_root() const -> nodes::node*
{
    // The 'root' getter returns the equivalent 'root' attribute value that is stored in the private class.
    ACCESS_PIMPL(const abstract_iterator);
    return d->root.get();
}


auto dom::node_iterators::abstract_iterator::get_what_to_show() const -> ext::number<ulong>
{
    // The 'what_to_show' getter returns the equivalent 'what_to_show' attribute value that is stored in the private
    // class.
    ACCESS_PIMPL(const abstract_iterator);
    return d->what_to_show;
}


auto dom::node_iterators::abstract_iterator::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("filter", &abstract_iterator::get_filter)
        .property("root", &abstract_iterator::get_root)
        .property("whatToShow", &abstract_iterator::get_what_to_show)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

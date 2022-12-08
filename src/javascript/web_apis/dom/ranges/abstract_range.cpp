#include "abstract_range.hpp"
#include "abstract_range_private.hpp"




auto dom::node_ranges::abstract_range::get_start_container() const -> nodes::node*
{
    // The 'start_container' getter returns the node of the 'start' attribute value that is stored in the private class.
    ACCESS_PIMPL(const abstract_range);
    return d->start->node.get();
}


auto dom::node_ranges::abstract_range::get_start_offset() const -> ext::number<ulong>
{
    // The 'start_offset' getter returns the offset of the 'start' attribute value that is stored in the private class.
    ACCESS_PIMPL(const abstract_range);
    return d->start->offset;
}


auto dom::node_ranges::abstract_range::get_end_container() const ->  nodes::node*
{
    // The 'end_container' getter returns the node of the 'end' attribute value that is stored in the private class.
    ACCESS_PIMPL(const abstract_range);
    return d->end->node.get();
}


auto dom::node_ranges::abstract_range::get_end_offset() const -> ext::number<ulong>
{
    // The 'end_offset' getter returns the offset of the 'end' attribute value that is stored in the private class.
    ACCESS_PIMPL(const abstract_range);
    return d->end->offset;
}


auto dom::node_ranges::abstract_range::get_collapsed() const -> ext::boolean
{
    return detail::is_range_collapsed(this);
}


auto dom::node_ranges::abstract_range::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate) -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<dom_object>()
        .property("startContainer", &abstract_range::get_start_container)
        .property("startOffset", &abstract_range::get_start_offset)
        .property("endContainer", &abstract_range::get_end_container)
        .property("endOffset", &abstract_range::get_end_offset)
        .property("collapsed", &abstract_range::get_collapsed)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

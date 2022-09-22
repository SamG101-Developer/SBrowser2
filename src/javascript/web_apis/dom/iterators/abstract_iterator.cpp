#include "abstract_iterator.hpp"

#include "dom/detail/traversal_internals.hpp"
#include "dom/iterators/node_filter.hpp"
#include "dom/nodes/element.hpp"
#include "dom/nodes/document.hpp"
#include "dom/other/dom_implementation.hpp"


dom::node_iterators::abstract_iterator::abstract_iterator()
        : INIT_PIMPL
{
    d_ptr->filter = nullptr;
    d_ptr->root = nullptr;
    d_ptr->what_to_show = 0;
}


auto dom::node_iterators::abstract_iterator::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<abstract_iterator>{isolate}
        .inherit<dom_object>()
        .property("filter", &abstract_iterator::get_filter)
        .property("root", &abstract_iterator::get_root)
        .property("whatToShow", &abstract_iterator::get_what_to_show)
        .auto_wrap_objects();

    return std::move(conversion);
}

#include "shadow_root.hpp"

#include "dom/events/event.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/element.hpp"


dom::nodes::shadow_root::shadow_root()
        : delegates_focus(false)
{}


auto dom::nodes::shadow_root::get_the_parent(
        events::event* event)
        -> event_target*
{
    auto event_composed = event->composed();
    auto* event_root = detail::tree_internals::root(dynamic_cast<node*>(event->path()->front()->invocation_target));

    return !event_composed && event_root == this ? nullptr : host();
}


auto dom::nodes::shadow_root::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    v8pp::class_<shadow_root>{isolate}
            .inherit<document_fragment>()
            .inherit<mixins::document_or_shadow_root>()
            .var("host", &shadow_root::host, true)
            .var("mode", &shadow_root::mode, true)
            .var("slotAssignment", &shadow_root::slot_assignment, true)
            .var("delegatesFocus", &shadow_root::delegates_focus, true)
            .auto_wrap_objects();
}

#include "shadow_root.hpp"

#include "dom/events/event.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/element.hpp"


dom::nodes::shadow_root::shadow_root() : INIT_PIMPL
{
    event_target::d_ptr->get_the_parent =
            [this](events::event* event)
            {
                return event->d_ptr->composed && !event->d_ptr->path.empty() && detail::root(dom_cast<node*>(event->d_ptr->path[0]->invocation_target)) == this
                        ? nullptr : document_fragment::d_ptr->host;
            };
}



auto dom::nodes::shadow_root::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    v8pp::class_<shadow_root>{isolate}
        .inherit<document_fragment>()
        .inherit<mixins::document_or_shadow_root>()
        .property("host", &shadow_root::get_host)
        .property("mode", &shadow_root::get_mode)
        .property("slotAssignment", &shadow_root::get_slot_assignment)
        .property("delegatesFocus", &shadow_root::get_delegates_focus)
        .auto_wrap_objects();
}

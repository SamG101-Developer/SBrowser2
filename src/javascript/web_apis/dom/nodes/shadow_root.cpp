#include "shadow_root.hpp"

#include "dom/events/event.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/element.hpp"


dom::nodes::shadow_root::shadow_root()
{
    INIT_PIMPL(shadow_root);
    ACCESS_PIMPL(shadow_root);

    d->get_the_parent =
            [this, d](events::event* event)
            {
                return event->d_func()->composed && !event->d_func()->path.empty() && detail::root(dom_cast<node*>(event->d_func()->path[0]->invocation_target)) == this
                        ? nullptr : d->host;
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

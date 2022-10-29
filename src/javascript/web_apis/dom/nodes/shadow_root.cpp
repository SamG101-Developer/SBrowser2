#include "shadow_root.hpp"
#include "shadow_root_private.hpp"

#include "dom/events/event.hpp"
#include "dom/events/event_private.hpp"
#include "dom/detail/event_internals.hpp"
#include "dom/detail/tree_internals.hpp"
#include "dom/nodes/element.hpp"
#include "node.hpp"


dom::nodes::shadow_root::shadow_root()
{
    INIT_PIMPL(shadow_root);
    ACCESS_PIMPL(shadow_root);

    d->get_the_parent =
            [this, d](events::event* event)
            {
                return event->d_func()->composed
                        && !event->d_func()->path.empty()
                        && detail::root(dom_cast<node*>(event->d_func()->path[0]->invocation_target)) == this
                    ? nullptr : d->host;
            };
}


auto dom::nodes::shadow_root::get_host() const -> dom::nodes::element*
{
    // The 'host' getter returns the equivalent 'host' attribute value that is stored in the private class.
    ACCESS_PIMPL(const shadow_root);
    return d->host;
}


auto dom::nodes::shadow_root::get_mode() const -> detail::shadow_root_mode_t
{
    // The 'mode' getter returns the equivalent 'mode' attribute value that is stored in the private class.
    ACCESS_PIMPL(const shadow_root);
    return d->mode;
}


auto dom::nodes::shadow_root::get_slot_assignment() const -> detail::slot_assignment_mode_t
{
    // The 'slot_assignment' getter returns the equivalent 'slot_assignment' attribute value that is stored in the
    // private class.
    ACCESS_PIMPL(const shadow_root);
    return d->slot_assignment;
}


auto dom::nodes::shadow_root::get_delegates_focus() const -> ext::boolean
{
    // The 'delegates_focus' getter returns the equivalent 'delegates_focus' attribute value that is stored in the
    // private class.
    ACCESS_PIMPL(const shadow_root);
    return d->delegates_focus;
}


auto dom::nodes::shadow_root::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<shadow_root>{isolate}
        .inherit<document_fragment>()
        .inherit<mixins::document_or_shadow_root>()
        .property("host", &shadow_root::get_host)
        .property("mode", &shadow_root::get_mode)
        .property("slotAssignment", &shadow_root::get_slot_assignment)
        .property("delegatesFocus", &shadow_root::get_delegates_focus)
        .auto_wrap_objects();

    return std::move(conversion);
}

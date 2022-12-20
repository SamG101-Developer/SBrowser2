module;
#include "ext/macros/pimpl.hpp"
#include "javascript/macros/expose.hpp"


module apis.dom.shadow_root;
import apis.dom.shadow_root_private;

import ext.core;


dom::shadow_root::shadow_root()
{
    INIT_PIMPL;
    ACCESS_PIMPL;

    d->get_the_parent = [this, d](events::event* event)
    {
        return event->d_func()->composed
                && !event->d_func()->path.empty()
                && detail::root(dom_cast<node*>(event->d_func()->path[0]->invocation_target)) == this
            ? nullptr : d->host;
    };
}


auto dom::shadow_root::get_host() const -> dom::element*
{
    // The 'host' getter returns the equivalent 'host' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->host;
}


auto dom::shadow_root::get_mode() const -> detail::shadow_root_mode_t
{
    // The 'mode' getter returns the equivalent 'mode' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->mode;
}


auto dom::shadow_root::get_slot_assignment() const -> detail::slot_assignment_mode_t
{
    // The 'slot_assignment' getter returns the equivalent 'slot_assignment' attribute value that is stored in the
    // private class.
    ACCESS_PIMPL;
    return d->slot_assignment;
}


auto dom::shadow_root::get_delegates_focus() const -> ext::boolean
{
    // The 'delegates_focus' getter returns the equivalent 'delegates_focus' attribute value that is stored in the
    // private class.
    ACCESS_PIMPL;
    return d->delegates_focus;
}


auto dom::shadow_root::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<self_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<document_fragment>()
        .inherit<mixins::document_or_shadow_root>()
        .property("host", &shadow_root::get_host)
        .property("mode", &shadow_root::get_mode)
        .property("slotAssignment", &shadow_root::get_slot_assignment)
        .property("delegatesFocus", &shadow_root::get_delegates_focus)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

module;
#include "ext/macros/macros.hpp"
#include "javascript/macros/expose.hpp"


module apis.dom.processing_instruction;
import apis.dom.processing_instruction_private;
import ext.core;


dom::processing_instruction::processing_instruction()
{
    INIT_PIMPL;
}


auto dom::processing_instruction::get_target() const -> ext::string_view
{
    // The 'target' getter returns the equivalent 'target' attribute value that is stored in the private class.
    ACCESS_PIMPL;
    return d->target;
}


auto dom::processing_instruction::set_data(ext::string new_data) -> ext::string
{
    // The 'data' setter sets the equivalent 'data' attribute value that is stored in the private class to the
    // 'new_data'.
    ACCESS_PIMPL;

    d->data = new_data;
    css::detail::processing_instruction_prolog_steps(this);
}


auto dom::processing_instruction::_to_v8(
        js::env::module_t E,
        v8::Isolate* isolate)
        -> ext::tuple<bool, v8pp::class_<this_t>>
{
    V8_INTEROP_CREATE_JS_OBJECT
        .inherit<character_data>()
        .inherit<css::cssom::mixins::link_style>()
        .property("target", &processing_instruction::get_target)
        .auto_wrap_objects();

    return V8_INTEROP_SUCCESSFUL_CONVERSION;
}

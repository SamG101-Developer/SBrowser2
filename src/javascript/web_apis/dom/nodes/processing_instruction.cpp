#include "processing_instruction.hpp"
#include "processing_instruction_private.hpp"

#include "css/cssom/detail/miscellaneous_query_internals.hpp"


dom::nodes::processing_instruction::processing_instruction()
{
    INIT_PIMPL(processing_instruction)
}


auto dom::nodes::processing_instruction::get_target() const -> ext::string
{
    // The 'target' getter returns the equivalent 'target' attribute value that is stored in the private class.
    ACCESS_PIMPL(const processing_instruction);
    return d->target;
}


auto dom::nodes::processing_instruction::set_data(ext::string new_data) -> ext::string
{
    // The 'data' setter sets the equivalent 'data' attribute value that is stored in the private class to the
    // 'new_data'.
    ACCESS_PIMPL(processing_instruction);

    d->data = new_data;
    css::detail::processing_instruction_prolog_steps(this);
}


auto dom::nodes::processing_instruction::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<processing_instruction>{isolate}
        .inherit<character_data>()
        .inherit<css::cssom::mixins::link_style>()
        .property("target", &processing_instruction::get_target)
        .auto_wrap_objects();

    return std::move(conversion);
}

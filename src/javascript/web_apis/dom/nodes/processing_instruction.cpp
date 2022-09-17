#include "processing_instruction.hpp"

#include "css/cssom/detail/miscellaneous_query_internals.hpp"


auto dom::nodes::processing_instruction::set_data(
        const decltype(data)::value_t & val) -> void
{
    guard_property(data);
    *data = val;

    css::detail::processing_instruction_prolog_steps(this);
}


auto dom::nodes::processing_instruction::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<processing_instruction>{isolate}
            .inherit<character_data>()
            .var("target", &processing_instruction::target, true)
            .auto_wrap_objects();
}

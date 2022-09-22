#include "processing_instruction.hpp"

#include "css/cssom/detail/miscellaneous_query_internals.hpp"


auto dom::nodes::processing_instruction::set_data(
        const decltype(data)::value_t & val) -> void
{
    character_data::d_ptr->data = val;
    css::detail::processing_instruction_prolog_steps(this);
}


auto dom::nodes::processing_instruction::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<processing_instruction>{isolate}
            .inherit<character_data>()
            .var("target", &processing_instruction::target, true)
            .auto_wrap_objects();

    return std::move(conversion);
}

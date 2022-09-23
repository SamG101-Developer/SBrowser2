#include "processing_instruction.hpp"

#include "css/cssom/detail/miscellaneous_query_internals.hpp"


dom::nodes::processing_instruction::processing_instruction() : INIT_PIMPL {}


auto dom::nodes::processing_instruction::set_data(ext::string val) -> ext::string
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
            .property("target", &processing_instruction::get_target)
            .auto_wrap_objects();

    return std::move(conversion);
}

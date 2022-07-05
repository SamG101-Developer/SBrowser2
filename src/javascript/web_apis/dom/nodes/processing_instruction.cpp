#include "processing_instruction.hpp"


auto dom::nodes::processing_instruction::to_v8(
        v8::Isolate* isolate)
        const && -> ext::any
{
    return v8pp::class_<processing_instruction>{isolate}
            .inherit<character_data>()
            .var("target", &processing_instruction::target, true)
            .auto_wrap_objects();
}

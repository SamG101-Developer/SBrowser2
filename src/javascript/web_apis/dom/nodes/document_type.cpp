#include "document_type.hpp"


auto dom::nodes::document_type::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<document_type>{isolate}
            .inherit<node>()
            .inherit<mixins::child_node>()
            .var("name", &document_type::name, true)
            .var("publicId", &document_type::public_id, true)
            .var("systemId", &document_type::system_id, true)
            .auto_wrap_objects();

    return std::move(conversion);
}

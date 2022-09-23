#include "document_type.hpp"


auto dom::nodes::document_type::to_v8(
        v8::Isolate* isolate)
        -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<document_type>{isolate}
        .inherit<node>()
        .inherit<mixins::child_node>()
        .property("name", &document_type::get_name)
        .property("publicId", &document_type::get_public_id)
        .property("systemId", &document_type::get_system_id)
        .auto_wrap_objects();

    return std::move(conversion);
}

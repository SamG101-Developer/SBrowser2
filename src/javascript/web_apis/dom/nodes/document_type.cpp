#include "document_type.hpp"
#include "document_type_private.hpp"


dom::nodes::document_type::document_type()
{
    INIT_PIMPL(document_type);
}


auto dom::nodes::document_type::get_node_name() const -> ext::string
{
    ACCESS_PIMPL(const document_type);
    return d->name;
}


auto dom::nodes::document_type::get_name() const -> ext::string
{
    ACCESS_PIMPL(const document_type);
    return d->name;
}


auto dom::nodes::document_type::get_public_id() const -> ext::string
{
    ACCESS_PIMPL(const document_type);
    return d->public_id;
}


auto dom::nodes::document_type::get_system_id() const -> ext::string
{
    ACCESS_PIMPL(const document_type);
    return d->system_id;
}


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

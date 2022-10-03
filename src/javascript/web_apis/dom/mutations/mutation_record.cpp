#include "mutation_record.hpp"
#include "mutation_record_private.hpp"


auto dom::mutations::mutation_record::get_type() const -> ext::string_view
{
    ACCESS_PIMPL(const mutation_record);
    return d->type;
}


auto dom::mutations::mutation_record::get_attribute_name() const -> ext::string_view
{
    ACCESS_PIMPL(const mutation_record);
    return d->attribute_name;
}


auto dom::mutations::mutation_record::get_attribute_namespace() const -> ext::string_view
{
    ACCESS_PIMPL(const mutation_record);
    return d->attribute_namespace;
}


auto dom::mutations::mutation_record::get_old_value() const -> ext::string_view
{
    ACCESS_PIMPL(const mutation_record);
    return d->old_value;
}


auto dom::mutations::mutation_record::get_target() const -> nodes::node*
{
    ACCESS_PIMPL(const mutation_record);
    return d->target;
}


auto dom::mutations::mutation_record::get_previous_sibling() const -> nodes::node*
{
    ACCESS_PIMPL(const mutation_record);
    return d->previous_sibling;
}


auto dom::mutations::mutation_record::get_next_sibling() const -> nodes::node*
{
    ACCESS_PIMPL(const mutation_record);
    return d->next_sibling;
}


auto dom::mutations::mutation_record::get_added_nodes() const -> ext::vector_span<nodes::node*>
{
    ACCESS_PIMPL(const mutation_record);
    return d->added_nodes;
}


auto dom::mutations::mutation_record::get_removed_nodes() const -> ext::vector_span<nodes::node*>
{
    ACCESS_PIMPL(const mutation_record);
    return d->removed_nodes;
}

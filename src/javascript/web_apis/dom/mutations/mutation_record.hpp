#ifndef SBROWSER2_MUTATION_RECORD_HPP
#define SBROWSER2_MUTATION_RECORD_HPP

#include "dom_object.hpp"
namespace dom::mutations {class mutation_record;}

#include "ext/vector.hpp"

#include "dom/mutations/mutation_record_private.hpp"


class dom::mutations::mutation_record
        : public virtual dom_object
{
public constructors:
    mutation_record();
    MAKE_PIMPL(mutation_record);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_GETTER(type, ext::string) {return d_ptr->type;}
    DEFINE_GETTER(attribute_name, ext::string) {return d_ptr->attribute_name;}
    DEFINE_GETTER(attribute_namespace, ext::string) {return d_ptr->attribute_namespace;}
    DEFINE_GETTER(old_value, ext::string) {return d_ptr->old_value;}

    DEFINE_GETTER(target, nodes::node*) {return d_ptr->target;}
    DEFINE_GETTER(previous_sibling, nodes::node*) {return d_ptr->previous_sibling;}
    DEFINE_GETTER(next_sibling, nodes::node*) {return d_ptr->next_sibling;}

    DEFINE_GETTER(added_nodes, ext::vector<nodes::node*>&) {return d_ptr->added_nodes;}
    DEFINE_GETTER(removed_nodes, ext::vector<nodes::node*>&) {return d_ptr->added_nodes;}
};


#endif //SBROWSER2_MUTATION_RECORD_HPP

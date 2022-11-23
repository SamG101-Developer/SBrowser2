#ifndef SBROWSER2_MUTATION_RECORD_HPP
#define SBROWSER2_MUTATION_RECORD_HPP

#include "dom_object.hpp"
namespace dom::mutations {class mutation_record;}
namespace dom::mutations {class mutation_record_private;}

#include "ext/vector.hpp"
#include "ext/span.hpp"
namespace dom::nodes {class node;}


class dom::mutations::mutation_record
        : public virtual dom_object
{
public constructors:
    mutation_record();
    MAKE_PIMPL(mutation_record);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(type, ext::string_view);
    DEFINE_GETTER(attribute_name, ext::string_view);
    DEFINE_GETTER(attribute_namespace, ext::string_view);
    DEFINE_GETTER(old_value, ext::string_view);

    DEFINE_GETTER(target, nodes::node*);
    DEFINE_GETTER(previous_sibling, nodes::node*);
    DEFINE_GETTER(next_sibling, nodes::node*);

    DEFINE_GETTER(added_nodes, ext::vector_span<nodes::node*>);
    DEFINE_GETTER(removed_nodes, ext::vector_span<nodes::node*>);
};


#endif //SBROWSER2_MUTATION_RECORD_HPP

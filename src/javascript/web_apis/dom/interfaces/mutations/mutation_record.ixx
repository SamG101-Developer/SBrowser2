module;
#include "ext/macros.hpp"


export module apis.dom.mutation_record;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PUBLIC_CLASS(dom, mutation_record) final
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

    DEFINE_GETTER(target, node*);
    DEFINE_GETTER(previous_sibling, node*);
    DEFINE_GETTER(next_sibling, node*);

    DEFINE_GETTER(added_nodes, ext::span<node*>);
    DEFINE_GETTER(removed_nodes, ext::span<node*>);
};

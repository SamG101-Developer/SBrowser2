module;
#include "ext/macros.hpp"


export module apis.dom.node:p;
import apis.dom.event_target;

IMPORT_ALL_TYPES(dom);
IMPORT_ALL_TYPES(html);


DEFINE_PRIVATE_CLASS(dom, node)
        : dom::event_target_private
{
public:
    MAKE_QIMPL(node);
    friend class dom::mutation_observer;
    using get_root_node_options_t = ext::map<ext::string, ext::any>;

public:
    ext::vector<std::unique_ptr<detail::registered_observer_t>> registered_observer_list;
    std::observer_ptr<document> node_document;

    ext::vector<std::unique_ptr<node>> child_nodes;
    std::observer_ptr<node> parent_node;
};

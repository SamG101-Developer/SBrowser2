module;
#include "ext/macros.hpp"
#include <memory>


export module apis.dom.abstract_iterator:p;
import apis.dom_object;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, abstract_iterator)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(abstract_iterator);

public:
    ext::boolean active_flag;

    std::observer_ptr<node> root;
    ext::number<ulong> what_to_show;
    std::unique_ptr<node_filter> node_filter;
};

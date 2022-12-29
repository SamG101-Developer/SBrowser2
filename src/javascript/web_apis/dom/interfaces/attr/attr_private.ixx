module;
#include "ext/macros.hpp"


export module apis.dom.attr_private;
import apis.dom.node;

IMPORT_ALL_TYPES(dom);


DEFINE_PRIVATE_CLASS(dom, attr)
        : node_private
{
public:
    MAKE_QIMPL(attr);

public:
    ext::string namespace_;
    ext::string namespace_prefix;
    ext::string local_name;
    ext::string value;
    std::observer_ptr<element> element;

public:
    auto qualified_name() const -> ext::string;
};

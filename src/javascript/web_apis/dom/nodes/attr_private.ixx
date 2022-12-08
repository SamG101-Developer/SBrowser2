module;
#include "ext/macros/pimpl.hpp"


module apis.dom.attr_private;
import apis.dom.node_private;
import ext.string;


DEFINE_PRIVATE_CLASS(dom, attr)
        : node_private
{
    MAKE_QIMPL(attr);

    ext::string namespace_;
    ext::string namespace_prefix;
    ext::string local_name;
    ext::string value;
    std::observer_ptr<dom::nodes::element> element;
};

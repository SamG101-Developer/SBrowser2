module;
#include "ext/macros.hpp"


export module apis.dom_parsing.xml_serializer:p;
import apis.dom_object;


DEFINE_PRIVATE_CLASS(dom_parsing, xml_serializer)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(xml_serializer);
};

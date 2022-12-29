module;
#include "ext/macros/macros.hpp"


export module apis.dom_parsing.xml_serializer_private;
import apis.dom_object_private;


DEFINE_PRIVATE_CLASS(dom_parsing, xml_serializer)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(xml_serializer);
};

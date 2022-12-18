module;
#include "ext/macros/pimpl.hpp"


export module apis.dom_parsing.xml_serializer_private;
import apis._.dom_object_private;


DEFINE_PRIVATE_CLASS(dom_parsing, xml_serializer)
        : virtual dom_object_private
{
public:
    MAKE_QIMPL(xml_serializer);
};

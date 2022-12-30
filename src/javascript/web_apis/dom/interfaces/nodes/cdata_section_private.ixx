module;
#include "ext/macros.hpp"


export module apis.dom.cdata_section:p;
import apis.dom.text;


DEFINE_PRIVATE_CLASS(dom, cdata_section)
        : text_private
{
public:
    MAKE_QIMPL(cdata_section);
};

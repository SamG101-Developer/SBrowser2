module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.cdata_section_private;
import apis.dom.text_private;


DEFINE_PRIVATE_CLASS(dom, cdata_section)
        : text_private
{
    MAKE_QIMPL(cdata_section);
};

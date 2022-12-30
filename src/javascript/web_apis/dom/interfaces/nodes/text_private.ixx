module;
#include "ext/macros.hpp"


export module apis.dom.text:p;
import apis.dom.character_data;
import apis.dom.mixins.slottable;


DEFINE_PRIVATE_CLASS(dom, text)
        : dom::character_data_private
        , dom::slottable_private
{
public:
    MAKE_QIMPL(text);
};

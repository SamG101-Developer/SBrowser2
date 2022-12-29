module;
#include "ext/macros/pimpl.hpp"


export module apis.dom.text_private;
import apis.dom.character_data_private;
import apis.dom.mixins.slottable_private;


DEFINE_PRIVATE_CLASS(dom, text)
        : dom::character_data_private
        , dom::slottable_private
{
public:
    MAKE_QIMPL(text);
};

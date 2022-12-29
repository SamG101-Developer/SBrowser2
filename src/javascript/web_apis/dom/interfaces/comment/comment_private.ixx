module;
#include "ext/macros.hpp"


export module apis.dom.comment_private;
import apis.dom.character_data;


DEFINE_PRIVATE_CLASS(dom, comment)
        : character_data_private
{
public:
    MAKE_QIMPL(comment);
};

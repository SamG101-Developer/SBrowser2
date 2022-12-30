module;
#include "ext/macros.hpp"


export module apis.dom.processing_instruction:p;
import apis.dom.character_data;
import apis.css.cssom.mixins.link_style;

import ext.core;


DEFINE_PRIVATE_CLASS(dom::nodes, processing_instruction) final
        : dom::character_data_private
        , css::cssom::mixins::link_style_private
{
public:
    MAKE_QIMPL(processing_instruction);

public:
    ext::string target;
};

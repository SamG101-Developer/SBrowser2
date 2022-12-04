#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_PROCESSING_INSTRUCTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_PROCESSING_INSTRUCTION_PRIVATE_HPP

#include "ext/pimpl.ixx"
#include "dom/nodes/character_data_private.hpp"




DEFINE_PRIVATE_CLASS(dom::nodes, processing_instruction)
        : character_data_private
        , css::cssom::mixins::link_style_private
{
    MAKE_QIMPL(processing_instruction);

    ext::string target;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_PROCESSING_INSTRUCTION_PRIVATE_HPP

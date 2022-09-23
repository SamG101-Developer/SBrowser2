#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_PROCESSING_INSTRUCTION_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_PROCESSING_INSTRUCTION_PRIVATE_HPP

#include "dom/nodes/character_data_privatre.hpp"

#include "ext/pimpl.hpp"
#include "ext/string.hpp"


DEFINE_PRIVATE_CLASS(dom::nodes, processing_instruction)
        : character_data_private
        , css::cssom::mixins::link_style_private
{
    ext::string target;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_PROCESSING_INSTRUCTION_PRIVATE_HPP

#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_TEXT_PRIVATE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_TEXT_PRIVATE_HPP

#include "ext/pimpl.hpp"
#include "dom/nodes/character_data_private.hpp"
#include "dom/mixins/slottable_private.hpp"


DEFINE_PRIVATE_CLASS(dom::nodes, text)
        : character_data_private
        , mixins::slottable_private
{
    MAKE_QIMPL(text);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_DOM_NODES_TEXT_PRIVATE_HPP

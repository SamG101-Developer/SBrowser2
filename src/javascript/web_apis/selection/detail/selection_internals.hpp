#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SELECTION_DETAIL_SELECTION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SELECTION_DETAIL_SELECTION_INTERNALS_HPP


namespace selection::detail
{
    auto when_associating_new_range()
            -> void;

    auto when_disassociating_new_range()
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_SELECTION_DETAIL_SELECTION_INTERNALS_HPP

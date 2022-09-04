#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_DETAIL_CLIPBOARD_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_DETAIL_CLIPBOARD_INTERNALS_HPP

#include "ext/boolean.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include USE_INNER_TYPES(clipboard)

#include <QtGui/QClipboard>


namespace clipboard::detail
{
    auto system_clipboard()
            -> QClipboard*;

    auto system_clipboard_data()
            -> ext::map<ext::string, clipboard_item_data_t>;

    auto check_clipboard_read_permission()
            -> ext::boolean;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_DETAIL_CLIPBOARD_INTERNALS_HPP

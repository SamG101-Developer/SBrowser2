#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_HPP

#include "dom_object.hpp"
namespace html::dnd {class data_transfer_item;}

#include USE_INNER_TYPES(html)
namespace file_api {class file;}


class html::dnd::data_transfer_item
        : public virtual dom_object
{
public constructors:
    data_transfer_item() = default;

public js_methods:
    auto get_as_string(detail::function_string_callback_t&& callback) -> ext::string;
    auto get_as_file() -> file_api::file;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_HPP

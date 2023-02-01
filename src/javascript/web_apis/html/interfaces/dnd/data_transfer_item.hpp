#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_HPP


namespace html::dnd {class data_transfer_item;}
namespace html::dnd {class data_transfer_item_private;}

#include "ext/optional.ixx"
#include INCLUDE_INNER_TYPES(html)
namespace file_api {class file;}


class html::dnd::data_transfer_item
        : public virtual dom_object
{
public aliases:
    using function_string_callback_t = ext::function_view<void(ext::string_view data)>;

public constructors:
    data_transfer_item();
    MAKE_PIMPL(data_transfer_item);
    MAKE_V8_AVAILABLE;

private js_methods:
    auto get_as_string(ext::optional<function_string_callback_t> callback) const -> ext::string;
    auto get_as_file() const -> ext::optional<file_api::file>;

private js_properties:
    DEFINE_GETTER(type, ext::string_view);
    DEFINE_GETTER(kind, detail::drag_data_item_kind_t);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DND_DATA_TRANSFER_ITEM_HPP

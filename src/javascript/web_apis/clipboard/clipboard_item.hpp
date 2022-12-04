#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP

#include "dom_object.hpp"
namespace clipboard {class clipboard_item;}

#include "ext/promise.ixx"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include INCLUDE_INNER_TYPES(clipboard)
namespace file_api {class blob;}


class clipboard::clipboard_item
        : public virtual dom_object
{
public constructors:
    clipboard_item();
    clipboard_item(detail::clipboard_item_t&& underlying_data);
    clipboard_item(ext::map<ext::string, detail::clipboard_item_data_t>&& items, ext::map<ext::string, ext::any>&& options = {});

public js_methods:
    auto get_type(ext::string&& type) -> ext::promise<file_api::blob*>;

private js_properties:
    ext::property<detail::presentation_style_t> presentation_style;
    ext::property<ext::vector<ext::string>> types;

private cpp_members:
    MAKE_PIMPL(clipboard_item);
    MAKE_V8_AVAILABLE;

private js_properties:
    DEFINE_CUSTOM_GETTER(presentation_style);
    DEFINE_CUSTOM_GETTER(types);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP

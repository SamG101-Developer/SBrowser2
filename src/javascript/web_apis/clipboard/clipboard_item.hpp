#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP

#include "dom_object.hpp"
namespace clipboard {class clipboard_item;}

#include "ext/promise.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include USE_INNER_TYPES(clipboard)
namespace file_api {class blob;}


class clipboard::clipboard_item
        : public virtual dom_object
{
public constructors:
    DOM_CTORS(clipboard_item);
    clipboard_item(ext::map<ext::string, detail::clipboard_item_data_t>&& items, ext::map<ext::string, ext::any>&& options = {});

public js_methods:
    auto get_type(ext::string&& type) -> ext::promise<file_api::blob*>;

public js_properties:
    ext::property<detail::presentation_style_t> presentation_style;
    ext::property<ext::vector<ext::string>> types;

private cpp_properties:
    detail::clipboard_item_t m_clipboard_item;
    ext::vector<ext::string> m_types_array;

private cpp_accessors:
    DEFINE_GETTER(presentation_style);
    DEFINE_GETTER(types);
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP

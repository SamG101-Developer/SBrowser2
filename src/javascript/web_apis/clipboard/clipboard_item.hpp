#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP

#include "dom_object.hpp"
namespace clipboard {class clipboard_item;}

#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "clipboard/_typedefs.hpp"
namespace file_api {class blob;}


class clipboard::clipboard_item
        : public virtual dom_object
{
public constructors:
    clipboard_item(ext::any&& clipboard_item, v8::Local<v8::Context> realm);
    clipboard_item(ext::map<ext::string, detail::clipboard_item_data_t>&& items, ext::map<ext::string, ext::any>&& options = {});

public js_methods:
    auto get_type(ext::string_view type) -> std::promise<file_api::blob*>;

public js_properties:
    ext::property<detail::presentation_style_t> presentation_style;
    ext::property<ext::vector<ext::string>> types;

private cpp_properties:
    ext::any m_clipboard_item;
    ext::vector<ext::string> m_types_array;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_ITEM_HPP

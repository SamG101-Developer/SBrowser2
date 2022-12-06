#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_HPP


namespace clipboard {class clipboard;}


#include "ext/vector.hpp"
namespace clipboard {class clipboard_item;}

class clipboard::clipboard
        : public dom::nodes::event_target
{
public constructors:
    clipboard() = default;
    
public js_methods:
    auto read() -> ext::promise<ext::vector<clipboard_item>>;
    auto read_text() -> ext::promise<ext::string>;
    auto write(ext::vector<clipboard_item*> data) -> ext::promise<void>;
    auto write_text(ext::string&& data) -> ext::promise<void>;

private cpp_members:
    MAKE_V8_AVAILABLE;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_HPP

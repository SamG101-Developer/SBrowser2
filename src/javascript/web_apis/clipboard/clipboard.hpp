#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_HPP

#include "dom/nodes/event_target.hpp"
namespace clipboard {class clipboard;}

#include "ext/promise.hpp"
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
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CLIPBOARD_CLIPBOARD_HPP

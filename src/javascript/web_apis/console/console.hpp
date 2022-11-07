#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_HPP

#include "dom_object.hpp"
namespace console {class console;}
namespace console {class console_private;}

#include INCLUDE_INNER_TYPES(console)
#include "ext/map.hpp"
#include "ext/stack.hpp"
#include "ext/vector.hpp"

class console::console : virtual public dom_object
{
public constructors:
    console();
    MAKE_PIMPL(console);
    MAKE_V8_AVAILABLE;

public js_methods:
    // Logging
    template <typename ...Args>
    auto assert_(ext::boolean condition = false, Args&&... data) -> void;

    auto clear() -> void;

    template <typename ...Args>
    auto debug(Args&&... data) -> void;

    template <typename ...Args>
    auto error(Args&&... data) -> void;

    template <typename ...Args>
    auto info(Args&&... data) -> void;

    template <typename ...Args>
    auto log(Args&&... data) -> void;

    template <typename ...Args>
    auto warn(Args&&... data) -> void;

    template <typename ...Args>
    auto table(ext::vector<ext::tuple<Args...>>&& table_data = nullptr, ext::vector<ext::string>&& properties = {}) -> void;

    template <typename ...Args>
    auto trace(Args&&... data) -> void;

    template <typename T>
    auto dir(ext::any&& item, T&& options = nullptr) -> void;

    template <typename ...Args>
    auto dirxml(Args&&... data) -> void;

    // Count
    auto count(ext::string&& label = u8"default") -> void;

    auto count_reset(ext::string&& label = u8"default") -> void;

    // Grouping
    template <typename ...Args>
    auto group(Args&&... data) -> void;

    template <typename ...Args>
    auto group_collapsed(Args&&... data) -> void;

    auto group_end();

    // Timing
    auto time(ext::string&& label = u8"default") -> void;

    template <typename ...Args>
    auto time_log(ext::string&& label = u8"default", Args&&... data) -> void;

    auto time_end(ext::string&& label = u8"default") -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_HPP

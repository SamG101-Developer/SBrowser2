#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_HPP

#include "dom_object.hpp"
namespace console {class console;}

#include USE_INNER_TYPES(console)
#include "ext/map.hpp"
#include "ext/stack.hpp"
#include "ext/vector.hpp"

class console::console
{
    // Logging
    template <typename ...Args>
    static auto assert_(ext::boolean&& condition = false, Args&&... data) -> void;

    static auto clear() -> void;

    template <typename ...Args>
    static auto debug(Args&&... data) -> void;

    template <typename ...Args>
    static auto error(Args&&... data) -> void;

    template <typename ...Args>
    static auto info(Args&&... data) -> void;

    template <typename ...Args>
    static auto log(Args&&... data) -> void;

    template <typename ...Args>
    static auto warn(Args&&... data) -> void;

    template <typename ...Args>
    static auto table(ext::vector<ext::tuple<Args...>>&& table_data = nullptr, ext::vector<ext::string>&& properties = {}) -> void;

    template <typename ...Args>
    static auto trace(Args&&... data) -> void;

    template <typename T>
    static auto dir(ext::any&& item, T object = nullptr) -> void;

    template <typename ...Args>
    static auto dirxml(Args&&... data) -> void;

    // Count
    static auto count(ext::string&& label = "default") -> void;

    static auto count_reset(ext::string&& label = "default") -> void;

    // Grouping
    template <typename ...Args>
    static auto group(Args&&... data) -> void;

    template <typename ...Args>
    static auto group_collapsed(Args&&... data) -> void;

    static auto group_end();

    // Timing
    static auto time(ext::string&& label = "default") -> void;

    template <typename ...Args>
    static auto time_log(ext::string&& label = "default", Args&&... data);

    static auto time_end(ext::string&& label = "default") -> void;

private:
    static ext::stack<ext::string> m_group_stack;
    static ext::map<ext::any, ext::number<size_t>> m_count_map;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CONSOLE_CONSOLE_HPP

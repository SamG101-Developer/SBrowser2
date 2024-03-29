module;
#include "ext/macros.hpp"


export module apis.console.console;
import apis.dom_object;
import ext.mixins;


DEFINE_PUBLIC_CLASS(console, console) final
        : virtual public dom_object
        , public ext::singleton<console>
{
public constructors:
    console();
    MAKE_PIMPL(console);
    MAKE_V8_AVAILABLE(ALL);

private js_methods:
    // Logging
    auto clear() -> void;
    template <typename ...Args> auto assert_(ext::boolean condition = false, Args&&... data) -> void;
    template <typename ...Args> auto debug(Args&&... data) -> void;
    template <typename ...Args> auto error(Args&&... data) -> void;
    template <typename ...Args> auto info(Args&&... data) -> void;
    template <typename ...Args> auto log(Args&&... data) -> void;
    template <typename ...Args> auto warn(Args&&... data) -> void;
    template <typename ...Args> auto table(ext::vector<ext::tuple<Args...>>&& table_data = nullptr, ext::vector<ext::string>&& properties = {}) -> void;
    template <typename ...Args> auto trace(Args&&... data) -> void;
    template <typename ...Args> auto dirxml(Args&&... data) -> void;
    template <typename T> auto dir(ext::any&& item, T&& options = nullptr) -> void;

    // Count
    auto count(ext::string&& label = u"default") -> void;
    auto count_reset(ext::string&& label = u"default") -> void;

    // Grouping
    template <typename ...Args> auto group(Args&&... data) -> void;
    template <typename ...Args> auto group_collapsed(Args&&... data) -> void;
    auto group_end();

    // Timing
    template <typename ...Args>
    auto time_log(ext::string&& label = u"default", Args&&... data) -> void;
    auto time_end(ext::string&& label = u"default") -> void;
    auto time(ext::string&& label = u"default") -> void;
};

export module apis.console.detail;
import ext.core;


export namespace console::detail
{
    template <ext::type_is_enum E, typename ...Args>
    auto logger(E log_level, Args&&... args) -> void;

    template <typename ...Args>
    auto formatter(Args&&... args) -> ext::string;

    template <ext::type_is_enum E, typename ...Args>
    auto printer(E format_type, Args&&... data) -> void;
}

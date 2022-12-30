module;
#include "ext/macros.hpp"


export module apis.console.detail;
import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(console)
{
    template <ext::type_is_enum E, typename ...Args>
    auto logger(E log_level, Args&&... args) -> void;

    template <typename ...Args>
    auto formatter(Args&&... args) -> ext::string;

    template <ext::type_is_enum E, typename ...Args>
    auto printer(E format_type, Args&&... data) -> void;
};

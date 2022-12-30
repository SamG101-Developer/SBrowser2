module;
#include "ext/macros.hpp"


export module apis.gyroscope.detail;
import apis.gyroscope.types;

import ext.core;


DEFINE_FWD_DECL_NAMESPACE_DETAIL(gyroscope)
{
    auto construct_gyroscope_object(gyroscope* sensor, ext::map<ext::string, ext::any>&& options) -> void;
};

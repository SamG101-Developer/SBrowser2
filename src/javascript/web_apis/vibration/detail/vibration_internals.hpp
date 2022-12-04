#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIBRATION_DETAIL_VIBRATION_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIBRATION_DETAIL_VIBRATION_INTERNALS_HPP


#include <v8-forward.h>
#include INCLUDE_INNER_TYPES(vibration)

namespace vibration::detail
{
    auto processing_vibration_patterns(
            detail::vibrate_pattern_t&& pattern)
            -> ext::boolean;

    auto validate_and_normalize(
            vibrate_pattern_t&& pattern)
            -> vibrate_pattern_t;

    auto perform_vibration(
            v8::Local<v8::Object> global_object,
            vibrate_pattern_t&& pattern)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_VIBRATION_DETAIL_VIBRATION_INTERNALS_HPP

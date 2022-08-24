#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP

#include "ext/slot.hpp"
#include "ext/string.hpp"

namespace battery::algorithm_internals
{
    template <typename T>
    auto update_battery_status_and_notify(
            ext::slot<T>& slot,
            T&& new_value,
            ext::string&& event_name)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_BATTERY_DETAIL_ALGORITHM_INTERNALS_HPP

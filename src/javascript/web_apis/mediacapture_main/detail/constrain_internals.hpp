#pragma once
#ifndef SBROWSER2_CONSTRAIN_INTERNALS_HPP
#define SBROWSER2_CONSTRAIN_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/set.hpp"
#include "ext/string.hpp"
#include "ext/vector.hpp"
#include "ext/promise.hpp"
#include INCLUDE_INNER_TYPES(mediacapture_main)
namespace mediacapture::main::mixins {class constrainable;}

namespace mediacapture::detail
{
    auto apply_constrains_template_algorithm(
            main::mixins::constrainable* object,
            constraints_t&& new_constraints = {})
            -> ext::promise<void>;

    auto apply_constrains_algorithm(
            main::mixins::constrainable* object,
            constraints_t&& new_constraints = {})
            -> ext::string;

    auto fitness_distance(
            settings_t&& settings,
            constraints_t&& constraint_set)
            -> ext::number<double>;

    auto select_settings(
            main::mixins::constrainable* object,
            constraints_t&& new_constrains)
            -> ext::map<ext::string, ext::any>;

    auto get_user_media_specific_failure_allowed(
            ext::vector<ext::string>&&)
            -> ext::boolean;

    const ext::set<ext::string> allowed_constraints {
        "width", "height", "aspect_ratio", "frame_rate", "facing_mode", "resize_mode", "sample_rate", "sample_size",
        "echo_cancellation", "auto_gain_control", "noise_suppression", "latency", "channel_count", "device_id",
        "group"};
};


#endif //SBROWSER2_CONSTRAIN_INTERNALS_HPP

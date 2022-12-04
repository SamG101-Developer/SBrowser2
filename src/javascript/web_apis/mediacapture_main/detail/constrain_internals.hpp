#pragma once
#ifndef SBROWSER2_CONSTRAIN_INTERNALS_HPP
#define SBROWSER2_CONSTRAIN_INTERNALS_HPP



#include "ext/set.hpp"

#include "ext/vector.hpp"

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
        u"width", u"height", u"aspect_ratio", u"frame_rate", u"facing_mode", u"resize_mode", u"sample_rate",
        u"sample_size", u"echo_cancellation", u"auto_gain_control", u"noise_suppression", u"latency", u"channel_count",
        u"device_id", u"group"};
};


#endif //SBROWSER2_CONSTRAIN_INTERNALS_HPP

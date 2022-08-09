#pragma once
#ifndef SBROWSER2_CONSTRAIN_INTERNALS_HPP
#define SBROWSER2_CONSTRAIN_INTERNALS_HPP

#include "ext/any.hpp"
#include "ext/map.hpp"
#include "ext/string.hpp"
#include <future>
namespace mediacapture::main::mixins {class constrainable;}

namespace mediacapture::detail::constrain_internals
{
    auto apply_constrains_template_algorithm(
            main::mixins::constrainable* object,
            ext::map<ext::string, ext::any>&& new_constraints = {})
            -> std::promise<void>;

    auto apply_constrains_algorithm(
            main::mixins::constrainable* object,
            ext::map<ext::string, ext::any>&& new_constraints = {})
            -> ext::string;

    auto fitness_distance(
            ext::map<ext::string, ext::any>&& settings,
            ext::map<ext::string, ext::any>&& constraint_set)
            -> ext::number<double>;

    auto select_settings(
            main::mixins::constrainable* object,
            ext::map<ext::string, ext::any>&& new_constrains)
            -> ext::map<ext::string, ext::any>;
};


#endif //SBROWSER2_CONSTRAIN_INTERNALS_HPP

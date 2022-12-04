#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS__TYPEDEFS_HPP


#include "ext/map.ixx"

#include "ext/stack.ixx"
#include "ext/string.hpp"

namespace css::detail
{
    struct keyframe_t;

    enum class animation_play_state_t {IDLE, RUNNING, PAUSED, FINISHED};
    enum class animation_replace_state_t {ACTIVE, REMOVED, PERSISTED};
    enum class animation_effect_phase_t {BEFORE, ACTIVE, AFTER, IN_PLAY, CURRENT, IN_EFFECT};
    enum class animation_effect_direction_t {NORMAL, REVERSE, ALTERNATE, ALTERNATE_REVERSE};
    enum class animation_effect_fill_mode_t {NONE, FORWARDS, BACKWARDS, BOTH, AUTO};
    enum class property_animation_type_t {NOT_ANIMATABLE, DISCRETE, BY_COMPUTED_VALUE, REPEATABLE_LIST, PROSE};
    enum class composite_operation_t {REPLACE, ADD, ACCUMULATE};
    enum class composite_operation_or_auto_t {REPLACE, ADD, ACCUMULATE, AUTO};

    using time_value_t = ext::number<int>;
    using effect_stack_t = ext::stack<animation_effect_t*>;
    using document_timeline_options_t = ext::map<ext::string, ext::any>;
    using optional_effect_timing_t = ext::map<ext::string, ext::any>;
    using effect_timing_t = ext::map<ext::string, ext::any>;
    using computed_effect_timing_t = ext::map<ext::string, ext::any>;
    using keyframe_effect_options_t = ext::map<ext::string, ext::any>;
    using keyframe_animation_options_t = ext::map<ext::string, ext::any>;
    using get_animations_options_t = ext::map<ext::string, ext::any>;
    using base_computed_keyframe_t = ext::map<ext::string, ext::any>;
    using base_property_indexed_keyframe_t = ext::map<ext::string, ext::any>;
    using base_keyframe_t = ext::map<ext::string, ext::any>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS__TYPEDEFS_HPP

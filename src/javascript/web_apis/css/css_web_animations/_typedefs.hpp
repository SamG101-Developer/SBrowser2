#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS__TYPEDEFS_HPP

#include "ext/number.hpp"

namespace css::detail
{
    struct timeline_t;
    struct document_timeline_t;
    struct animation_t;
    struct animation_effect_t;

    enum class animation_play_state_t {IDLE, RUNNING, PAUSED, FINISHED};
    enum class animation_effect_phase_t {BEFORE, ACTIVE, AFTER, IN_PLAY, CURRENT, IN_EFFECT};
    enum class animation_effect_direction_t {BACKWARDS, FORWARDS};
    enum class animation_effect_fill_mode_t {NONE, FORWARDS, BACKWARDS, BOTH};

    using time_value_t = ext::number<int>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_CSS_CSS_WEB_ANIMATIONS__TYPEDEFS_HPP

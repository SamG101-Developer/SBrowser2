module;
#include "ext/macros.hpp"


export module apis.hr_time.performance:p;
import apis.dom.event_target;


DEFINE_PRIVATE_CLASS(hr_time, performance) : dom::event_target_private {};

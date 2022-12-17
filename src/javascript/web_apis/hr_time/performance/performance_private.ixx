module;
#include "ext/macros/pimpl.hpp"


export module apis.hr_time.performance_private;
import apis.dom.event_target_private;


DEFINE_PRIVATE_CLASS(hr_time, performance) : dom::event_target_private {};

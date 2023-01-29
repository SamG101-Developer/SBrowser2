module;
#include "ext/macros.hpp"


export module apis.paint_timing.performance_paint_timing:p;
import apis.performance_timeline.performance_entry;


DEFINE_PRIVATE_CLASS(paint_timing, performance_paint_timing) final
        : performance_timeline::performance_entry_private
{
public:
    MAKE_QIMPL(performance_paint_timing);
};

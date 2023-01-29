module;
#include "ext/macros.hpp"


export module apis.paint_timing.performance_paint_timing;
import apis.performance_timeline.performance_entry;


DEFINE_PUBLIC_CLASS(paint_timing, performance_paint_timing) final
        : public performance_timeline::performance_entry
{
public constructors:
    DOM_CTORS(performance_paint_timing);
    MAKE_PIMPL(performance_paint_timing);
    MAKE_V8_AVAILABLE(WINDOW);

private js_properties:
    DEFINE_GETTER(name, ext::string) override {return u8"paint";}
    DEFINE_GETTER(entry_type, ext::string) override {return u8"first-paint";} // TODO
    DEFINE_GETTER(start_time, hr_time::dom_high_res_time_stamp) override;
    DEFINE_GETTER(duration, hr_time::dom_high_res_time_stamp) override {return 0;};
};

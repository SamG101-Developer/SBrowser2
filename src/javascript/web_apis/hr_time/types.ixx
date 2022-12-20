module;
#include "ext/macros/pimpl.hpp"


export module apis.hr_time.types;
import ext.number;


DEFINE_FWD_DECL_NAMESPACE(hr_time)
{
    using dom_high_res_time_stamp = ext::number<double>;
    using epoch_time_stamp = ext::number<ulonglong>;

    class performance;
}


DEFINE_FWD_DECL_NAMESPACE_DETAIL(hr_time) {};

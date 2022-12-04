#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HR_TIME__TYPEDEFS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HR_TIME__TYPEDEFS_HPP




namespace hr_time::detail
{}


namespace hr_time // NOTE: no ::detail
{
    using dom_high_res_time_stamp = ext::number<double>;
    using epoch_time_stamp = ext::number<ulonglong>;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HR_TIME__TYPEDEFS_HPP

export module apis.hr_time.types;


import ext.number;

export namespace hr_time::detail {}


export namespace hr_time // NOTE: no ::detail (exposed to JS)
{
    using dom_high_res_time_stamp = ext::number<double>;
    using epoch_time_stamp = ext::number<ulonglong>;
}

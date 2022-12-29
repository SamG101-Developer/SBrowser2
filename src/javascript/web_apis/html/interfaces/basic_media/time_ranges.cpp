#include "time_ranges.hpp"
#include "time_ranges_private.hpp"


html::basic_media::time_ranges::time_ranges()
{
    INIT_PIMPL(time_ranges);
}


auto html::basic_media::time_ranges::start(ext::number<long> index) const -> ext::number<double>
{
    // Get the start of the range that is at 'index' position in the internal 'm_ranges' list of ranges. The start of
    // the range is the first element in the pair.
    ACCESS_PIMPL(const time_ranges);
    return d->linked_vector.at(*index).first;
}


auto html::basic_media::time_ranges::end(ext::number<long> index) const -> ext::number<double>
{
    // Get the end of the range that is at 'index' position in the internal 'm_ranges' list of ranges. The end of the
    // range is the second element in the pair.
    ACCESS_PIMPL(const time_ranges);
    return d->linked_vector.at(*index).second;
}


auto html::basic_media::time_ranges::to_v8(v8::Isolate* isolate) -> v8pp::class_<self_t>
{
    decltype(auto) conversion = v8pp::class_<time_ranges>{isolate}
        .function("start", &time_ranges::start)
        .function("end", &time_ranges::end)
        .auto_wrap_objects();

    return std::move(conversion);
}

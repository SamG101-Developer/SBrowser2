#include "time_ranges.hpp"

#include <v8pp/class.hpp>


html::basic_media::time_ranges::time_ranges()
{
    bind_get(length);
}


auto html::basic_media::time_ranges::start(
        const ext::number<long>& index)
        -> ext::number<double>
{
    // Get the start of the range that is at 'index' position in the internal 'm_ranges' list of ranges. The start of
    // the range is the first element in the pair.
    return m_ranges.at(*index).first;
}


auto html::basic_media::time_ranges::end(
        const ext::number<long>& index)
        -> ext::number<double>
{
    // Get the end of the range that is at 'index' position in the internal 'm_ranges' list of ranges. The end of the
    // range is the second element in the pair.
    return m_ranges.at(*index).second;
}


auto html::basic_media::time_ranges::get_length()
        const -> typename decltype(this->length)::value_t
{
    // Get the number of ranges being stored -- this is the number of pairs stored in the internal 'm_ranges' list of
    // ranges.
    return m_ranges.size();
}


auto html::basic_media::time_ranges::to_v8(
        v8::Isolate* isolate)
        const&& -> ext::any
{
    return v8pp::class_<time_ranges>{isolate}
        .function("start", &time_ranges::start)
        .function("end", &time_ranges::end)
        .var("length", &time_ranges::length, true)
        .auto_wrap_objects();
}

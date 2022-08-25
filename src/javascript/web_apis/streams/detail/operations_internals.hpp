#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_OPERATIONS_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_OPERATIONS_INTERNALS_HPP

#include "ext/number.hpp"
namespace streams {class readable_stream;}
namespace streams {class readable_stream_byob_reader;}
namespace streams {class readable_stream_default_reader;}

namespace streams::detail
{
    auto acquire_readable_stream_stream_byob_reader(
            readable_stream* stream)
             -> readable_stream_byob_reader;

    auto acquire_readable_stream_default_reader(
            readable_stream* stream)
            -> readable_stream_default_reader;

    template <typename F0, typename F1, typename F2, typename F3>
    auto create_readable_stream(
            F0&& start_algorithm,
            F1&& pull_algorithm,
            F2&& cancel_algorithm,
            ext::number<int> high_water_mark = 1,
            F3&& size_algorithm = [] {})
            -> readable_stream;

    template <typename F0, typename F1, typename F2>
    auto create_readable_byte_stream(
            F0&& start_algorithm,
            F1&& pull_algorithm,
            F2&& cancel_algorithm)
            -> readable_stream;

    auto initialize_readable_stream(
            readable_stream* stream)
            -> void;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_STREAMS_DETAIL_OPERATIONS_INTERNALS_HPP

#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_OUTPUT_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_OUTPUT_DETAIL_ALGORITHM_INTERNALS_HPP

namespace mediacapture::detail
{
    auto sink_no_longer_available()
            -> void;

    auto new_sink_available()
            -> void;

    auto on_page_load()
            -> void;
}

#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_MEDIACAPTURE_OUTPUT_DETAIL_ALGORITHM_INTERNALS_HPP

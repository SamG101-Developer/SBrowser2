#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LAZY_LOADING_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LAZY_LOADING_INTERNALS_HPP


#include "ext/number.ixx"
#include "ext/string.hpp"
namespace dom::nodes {class element;}

namespace html::detail
{
    auto will_lazy_load_element_steps(
            const dom::nodes::element* element)
            -> ext::boolean;

    auto start_intersection_observing_lazy_loading_element(
            const dom::nodes::element* element)
            -> void;

    auto stop_intersection_observing_a_lazy_loading_element(
            const dom::nodes::element* element)
            -> void;

    auto lazy_load_root_margin()
            -> ext::number<double>;
}


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_HTML_DETAIL_LAZY_LOADING_INTERNALS_HPP

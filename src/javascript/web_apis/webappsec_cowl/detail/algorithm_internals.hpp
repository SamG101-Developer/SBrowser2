#pragma once
#ifndef SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_ALGORITHM_INTERNALS_HPP
#define SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_ALGORITHM_INTERNALS_HPP

namespace webappsec::cowl {class label;}


namespace webappsec::detail
{
    auto label_normal_form_reduction(
            cowl::label* label)
            -> cowl::label;
};


#endif //SBROWSER2_SRC_JAVASCRIPT_WEB_APIS_WEBAPPSEC_COWL_DETAIL_ALGORITHM_INTERNALS_HPP
